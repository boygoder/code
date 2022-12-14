from Enet import Seg_Model
from scipy.optimize import curve_fit, leastsq
from torch.autograd import Variable
from skimage import morphology
# from dto import result
import numpy as np
import torch
import math
import time
import uuid
import cv2
import os


def cv_show(name, image, seconds=0.01, cv_type=cv2.WINDOW_NORMAL):
    cv2.namedWindow(str(name), cv_type)
    cv2.imshow(str(name), image.astype(np.uint8))
    if cv2.waitKey(int(seconds * 1000)) & 0xFF == ord('q'):
        cv2.destroyWindow(str(name))


class cableDetection:
    def __init__(self, pictureClassCode=None, algorithmCode=None, modelFile=None, width=None, height=None,
                 gpuDevice=None):
        if pictureClassCode == None:
            return

        self.pictureClassCode = pictureClassCode
        self.algorithmCode = algorithmCode
        modelFile = os.path.abspath(modelFile)

        # device_ids = str(gpuDevice).split(',')
        # os.environ["CUDA_VISIBLE_DEVICES"] = device_ids[0]
        self.device = torch.device(f'cuda:{gpuDevice}' if torch.cuda.is_available() else 'cpu')
        self.model = self.load_model(modelFile)

        self.height = height
        self.width = width
        self.iterate_time = 6

    def catenary_func(self, x, a, b, c):
        return a * np.cosh((x - b) / a) + c

    # 迭代扩展样本点，进行拟合
    def iterate_fit(self, crop_img, sample_pts_origin, param_origin):
        [image_y_max, image_x_max] = crop_img.shape[:2]
        num_curve = int(sample_pts_origin.shape[2])

        param_old = param_origin
        sample_pts_old = sample_pts_origin

        expansion_size = int(round(image_x_max / self.iterate_time))
        for time in range(0, self.iterate_time):
            pnt_num = sample_pts_old.shape[0]
            x_cut_min = sample_pts_old[0, 0, 0]
            x_cut_max = sample_pts_old[pnt_num - 1, 0, 0]
            if x_cut_min > expansion_size:
                x_cut_min = x_cut_min - expansion_size
            else:
                x_cut_min = 0

            if image_x_max - x_cut_max > expansion_size:
                x_cut_max = x_cut_max + expansion_size
            else:
                x_cut_max = image_x_max - 1

            x_cut_size = int(x_cut_max - x_cut_min + 1)
            sample_pts_new = np.zeros((x_cut_size, 2, num_curve))
            for i in range(0, num_curve):
                for x in range(0, x_cut_size):
                    sample_pts_new[x, 0, i] = x + x_cut_min

            for x in range(0, x_cut_size):
                for y in range(image_y_max - 1, -1, -1):
                    u = int(-y + image_y_max - 1)
                    v = int(x + x_cut_min)
                    if crop_img[u, v] == 1:
                        y_distance = np.zeros(num_curve)
                        for id in range(0, num_curve):
                            t = param_old[id, :]
                            y_fit = t[0] * np.cosh((v - t[1]) / t[0]) + t[2]
                            y_distance[id] = np.abs(y_fit - y)

                        # 寻找离这个点最近的曲线
                        min_distance = np.min(y_distance)
                        if min_distance <= 12:
                            curve_id = np.where(y_distance == min_distance)
                            sample_pts_new[x, 1, curve_id] = y

            param_new = np.zeros((num_curve, 3))
            for id in range(0, num_curve):
                sample_x = sample_pts_new[:, 0, id]
                sample_y = sample_pts_new[:, 1, id]
                # 将曲线中没有选定点的列删除
                zero_column = np.where(sample_y == 0)
                sample_x = np.delete(sample_x, zero_column)
                sample_y = np.delete(sample_y, zero_column)

                param_init = param_old[id, :]
                # [param, _] = leastsq(f_err, param_initial, args=(sample_y, sample_x))
                param, pcov = curve_fit(self.catenary_func, sample_x, sample_y, p0=param_init, method='dogbox',
                                        max_nfev=100000)
                param_new[id, :] = param

            # print("Iterate_time:%d \n" % time)
            for id in range(0, num_curve):
                a = param_new[id, 0]
                b = param_new[id, 1]
                c = param_new[id, 2]
                # print(f"y = {a:.3f} * cosh((x - ({b:.3f})) / {a:.3f}) + ({c:.3f})")
            param_old = param_new
            sample_pts_old = sample_pts_new

        return param_old, sample_pts_old

    def tidying_cable(self, pts, mask):
        rows, cols = mask.shape[0:2]

        # 1.1图像移动到中心
        min_rect = cv2.minAreaRect(pts)
        y_, x_ = int(rows / 2 - min_rect[0][0]), int(cols / 2 - min_rect[0][1])
        P = np.float32([[1, 0, x_], [0, 1, y_]])
        center_img = cv2.warpAffine(mask, P, (cols, rows))  # 图像移动到中心

        # 1.2图像变换成水平线方向
        [vy, vx, y, x] = cv2.fitLine(pts, cv2.DIST_L2, 0, 0.01, 0.01)
        theta_cos = math.acos(vy) * 180 / math.pi
        theta_sin = math.asin(vx) * 180 / math.pi

        angle = theta_cos - 90 if theta_cos * theta_sin < 0 else 90 - theta_cos
        M = cv2.getRotationMatrix2D((cols / 2, rows / 2), angle, 1.0)  # 参数分别为:旋转中心,旋转角度,图像缩放因子
        dst = cv2.warpAffine(center_img, M, (cols, rows))  # 仿射变换其三个参数分别为:输入图像,变换矩阵,输出图像大小
        #cv_show('dst', cv2.resize(dst, (1280, 720)), 0.1)
        crop_img = self.crop_img(cv2.resize(dst, (1280, 720)))
        crop_im, sample_pts_origin = self.get_sample_pts(crop_img)
        param_origin = self.initial_fit(crop_img, sample_pts_origin)
        # print(param_origin)
        param, sample_pts = self.iterate_fit(crop_img, sample_pts_origin, param_origin)

        fname = uuid.uuid1().hex[:-12]
        radians = self.calculate_radian(param, sample_pts, fname)
        # self.show_png(crop_img, param, fname)
        return radians

    def show_png(self, crop_img, param, fname=None):
        import matplotlib.pyplot as plt
        image_y_max, image_x_max = crop_img.shape
        num_curve = int(param.shape[0])
        plt.xlim((0, image_x_max))
        plt.ylim((image_y_max, 0))
        plt.imshow(crop_img, cmap="gray")
        for id in range(0, num_curve):
            t = param[id, :]
            x_fit = np.zeros(image_x_max)
            y_fit = np.zeros(image_x_max)
            for x in range(0, image_x_max):
                x_fit[x] = x
                y_fit[x] = t[0] * np.cosh((x - t[1]) / t[0]) + t[2]
            u_fit = - y_fit + image_y_max - 1
            plt.plot(x_fit, u_fit, color='green', linewidth=2)
        file = os.path.join('../cases/figs', f"{fname}_fit.png")
        plt.savefig(file)
        plt.show()

    # 计算弯曲度
    def calculate_radian(self, param, sample_pts, fname):
        num_curve = int(sample_pts.shape[2])
        radian = np.zeros(num_curve)
        for id in range(0, num_curve):
            sample_x = sample_pts[:, 0, id]
            sample_y = sample_pts[:, 1, id]
            # 将曲线中没有选定点的列删除。
            zero_column = np.where(sample_y == 0)
            sample_x = np.delete(sample_x, zero_column)
            sample_y = np.delete(sample_y, zero_column)

            # 取出样本点的起点和终点，画出直线。
            pnt_num = sample_x.shape[0]
            x_start = sample_x[0]
            y_start = sample_y[0]
            x_end = sample_x[pnt_num - 1]
            y_end = sample_y[pnt_num - 1]

            # 起点到终点的直线。
            k = (y_end - y_start) / (x_end - x_start)
            b = y_end - k * x_end

            # 计算曲线到直线的距离，取出最大值计算弯曲度
            line_length = np.sqrt(pow(x_end - x_start, 2) + pow(y_end - y_start, 2))
            distance = np.zeros(pnt_num)
            for i in range(0, pnt_num):
                distance[i] = np.abs(k * sample_x[i] - sample_y[i] + b) / np.sqrt(1 + k * k)

            max_distance = np.max(distance)
            radian[id] = max_distance / line_length
            # print("y = %f * x + %f \n" % (k, b))
        # print(radian)
        # if fname is not None:
        #     file = os.path.join(r'../cases/params', f"{fname}_param.txt")
        #     f = open(file, 'w', encoding='UTF-8')
        #     f.write("%12s %12s %12s \n" % ("a", "b", "c"))
        #     for i in range(0, num_curve):
        #         f.write(str(param[i, :]) + '\n')
        #     f.write("radian : " + str(radian))
        #     f.close()

        return radian

    def fitted_curve(self, func, xs, ys):
        pts_fit2 = np.polyfit(xs, ys, 2)  # 用抛物线拟合, 含3个系数
        # plot_y2 = pts_fit2[0] * xs ** 2 + pts_fit2[1] * xs + pts_fit2[2]
        # plot_y3 = pts_fit3[0] * xs ** 3 + pts_fit3[1] * xs ** 2 + pts_fit3[2] * xs + pts_fit3[3]
        # pts_fitted2 = np.array([np.transpose(np.vstack([xs, plot_y2]))])

        points_x = sorted(list(set(xs.tolist())))
        x_min, x_max = min(points_x), max(points_x)
        skip = 2
        if x_max - x_min > 120:
            skip = (x_max - x_min) // 120

        def check(i):
            return i % skip == 0

        points_x = list(filter(check, points_x))

        points_y = []
        for x in points_x:
            y = pts_fit2[0] * x ** 2 + pts_fit2[1] * x + pts_fit2[2]
            points_y.append(int(round(y, 0)))

        # img = cv2.cvtColor(binary.copy(), cv2.COLOR_GRAY2BGR)
        # cv2.polylines(img, [np.array(list(zip(points_x, points_y)))], False, (0, 0, 255), 3)
        # cv_show(920, img, 0.1)
        return points_x, points_y

    def initial_fit(self, crop_img, sample_pts):
        [image_y_max, image_x_max] = crop_img.shape[:2]
        num_curve = int(sample_pts.shape[2])
        param_origin = np.zeros((num_curve, 3))
        for i in range(0, num_curve):
            y = sample_pts[:, 1, i]
            x = sample_pts[:, 0, i]
            param_init = [image_y_max, image_x_max, -image_y_max]
            # [param, _] = leastsq(f_err, param_initial, args=(y, x))
            param, pcov = curve_fit(self.catenary_func, x, y, p0=param_init, method='dogbox', max_nfev=100000)
            param_origin[i, :] = param

        return param_origin

    def get_sample_pts(self, crop_img):
        num_curve, count = self.get_curve_num(crop_img)

        [image_y_max, image_x_max] = crop_img.shape[:2]
        length = 0
        start = end = 0
        share_index = 0
        while start < image_x_max and end < image_x_max:
            while start < image_x_max and count[start] != num_curve:
                start += 1
            end = start + 1
            while end < image_x_max and count[end] == num_curve:
                end += 1
            sublength = end - start
            if sublength > length:
                length = sublength
                share_index = start
            start = end + 1
        # print('截取起点:%d, 截取长度:%d' % (share_index, length))
        crop_im = crop_img[:, share_index: share_index + length - 1]
        crop_im_y_max, crop_im_x_max = crop_im.shape[:2]

        sample_pts = np.zeros((crop_im_x_max, 2, num_curve))
        for i in range(0, crop_im_x_max):
            curve_id = 0
            for j in range(crop_im_y_max - 1, -1, -1):
                x = i + share_index
                y = -j + crop_im_y_max - 1
                if crop_im[y, i] == 1:
                    sample_pts[i, 0, curve_id] = x
                    sample_pts[i, 1, curve_id] = j
                    curve_id += 1
        return crop_im, sample_pts

    def crop_img(self, img):
        _, binary = cv2.threshold(img, 144, 255, cv2.THRESH_BINARY)
        skeleton = morphology.skeletonize_3d(binary)
        ys, xs = np.where(skeleton == 255)
        x_min, x_max = np.min(xs), np.max(xs)
        y_min, y_max = np.min(ys), np.max(ys)

        crop_skeleton = skeleton[y_min:y_max, x_min:x_max]
        crop_skeleton[crop_skeleton == 255] = 1
        return crop_skeleton

    def get_curve_num(self, crop_img):
        _, image_x_max = crop_img.shape
        count = np.sum(crop_img, axis=0)
        num_curve = int(np.max(count))
        num_curve_part = np.where(count == num_curve)
        length = np.size(num_curve_part)
        # num_curve 股缆绳的水平最小长度, 1/20
        min_length = round(image_x_max / 20)
        while length < min_length:
            count[num_curve_part] = 0
            num_curve = int(np.max(count))
            num_curve_part = np.where(count == num_curve)
            length = np.size(num_curve_part)

        # print("判定缆绳数量为：%d" % num_curve)
        
        return num_curve, count

    def predict(self, input_image, params=None):
        resultList = []
        if params is not None:
            box = params['quadrilateral']
            rectangle = [[box['topLeft']['x'], box['topLeft']['y']],
                         [box['topRight']['x'], box['topRight']['y']],
                         [box['bottomRight']['x'], box['bottomRight']['y']],
                         [box['bottomLeft']['x'], box['bottomLeft']['y']]
                         ]
            pts = np.array(rectangle, dtype=np.int32)  # 摄像头采集皮带的角点
            mask = np.zeros(input_image.shape, dtype=np.uint8)
            cv2.fillPoly(mask, [pts], (255, 255, 255))
            input_image = cv2.bitwise_and(mask, input_image)
        # start = time.time()
        prediction = self.detect_model(input_image)  # 0背景,1拉绳
        # print(f'cable seg cost {time.time() - start}s...')

        gauss_img = cv2.GaussianBlur(prediction.copy(), ksize=(7, 7), sigmaX=1.5)
        gauss_img = cv2.morphologyEx(gauss_img, cv2.MORPH_OPEN, (7, 7), iterations=3)
        _, binary = cv2.threshold(gauss_img, 144, 255, cv2.THRESH_BINARY)

        num_labels, marker = cv2.connectedComponents(binary.copy(), connectivity=8)
        pred = cv2.cvtColor(prediction.copy(), cv2.COLOR_GRAY2BGR)
        count_curve = 0
        for k in range(1, num_labels):
            ys, xs = np.where(marker == k)
            if len(xs) == 0 or len(ys) == 0:
                continue
            pts = np.array(list(zip(ys, xs)), dtype=np.float32)
            """
            rect[0]:返回矩形的中心点(x, y),实际上为y行x列的像素点;      
            rect[1]:返回矩形的长和宽,在旋转角度上有很重要的作用;
            rect[2]:返回矩形的旋转角度,范围是(-90°, 0]
            """
            min_rect = cv2.minAreaRect(pts)  # 缆绳的最小外接矩形
            if max(min_rect[1]) > 500:
                mask = np.zeros(binary.shape[:2], np.uint8)
                mask[marker == k] = 255
                # 1、每股缆绳详细切分一根根
                if min(min_rect[1]) > 40:
                    curvatures = self.tidying_cable(pts, mask)
                    for c in curvatures:
                        d = {'curve_id': count_curve, 'curvature': c, 'points_x': None, 'points_y': None}
                        count_curve += 1
                        resultList.append(d)

        # 画图显示
        img_show = np.concatenate((input_image, pred), axis=1)
        img_show = cv2.resize(img_show, (512 * 2, 288))
        cv_show("frame", img_show, 0.01, cv2.WINDOW_NORMAL)

        if len(resultList) != 0:
            print(resultList)
        # return result.successReturn(resultList)
        return resultList

    def detect_model(self, input_image):
        # data = self.get_input_data(input_image)  # 1.5638182163238525s
        data = np.expand_dims(input_image, axis=0)  # 1.5357458591461182s
        data = data.transpose((0, 3, 1, 2))
        data = torch.from_numpy(data.astype(np.float32))

        with torch.no_grad():
            data = Variable(data.to(self.device))
            output = self.model(data)
            output = output.cpu().data.numpy()

            prediction = np.squeeze(output[:, 1, :, :])  # 0背景,1拉绳
            prediction = np.int64(prediction >= 0.7).astype(np.uint8)
            prediction[prediction != 0] = 255
            if len(data) > 1:
                prediction = self.concat_image(prediction, input_image.shape)
        return prediction

    def get_input_data(self, input_image):
        assert input_image.shape[:2] == (1440, 2560), "图片尺寸不是 2560 * 1440 "
        # 将图像等分为四个小块
        img_crop = np.zeros((12, 480, 640, 3), dtype=np.uint8)
        count = 0
        for j in range(0, 3):
            for k in range(0, 4):
                img_crop[count, :, :, :] = input_image[480 * j:480 * j + 480, 640 * k:640 * k + 640, :]
                count += 1
        inputs = img_crop.transpose((0, 3, 1, 2))  # (4,3,320,320)
        return inputs

    def concat_image(self, data, shape):
        # data --> (batch, c, h, w)
        N, h, w = data.shape[0:3]
        s, t = int(shape[0] / h), int(shape[1] / w)
        out = np.zeros((h * s, w * t))
        for i in range(s):
            for j in range(t):
                Slice = data[i * t + j, :, :]
                resize = Slice.squeeze()
                out[i * h:(i + 1) * h, j * w:(j + 1) * w] = resize
        return out.astype(np.uint8)

    def load_model(self, modelFile, device_ids=None, num_classes=2):
        model = Seg_Model(num_classes)
        checkpoint = torch.load(modelFile, map_location=self.device)
        model.load_state_dict(checkpoint['state_dict'], strict=True)

        # device = None if len(device_ids) < 2 else device_ids
        # model = DataParallel(model, device_ids=device)
        model = model.to(self.device)
        model.eval()
        return model


if __name__ == '__main__':
    import time
    import uuid
    import socket

    print('本机ip地址:', socket.gethostbyname_ex(socket.gethostname()))
    os.chdir(os.path.abspath(os.path.dirname(__file__)))
    params = None
    devices = '0'
    pictureClassCode = 'cable'
    algorithmCode = 'ENet'
    modelFile = r'best_net_NEW_LS20221111.ckpt'
    app = cableDetection(pictureClassCode, algorithmCode, modelFile, 2560, 1440, devices)

    vid = cv2.VideoCapture("./total.mp4")
    # params = {'quadrilateral': {'topLeft': {'x': 526.824, 'y': 50.4},
    #                             'topRight': {'x': 1865.216, 'y': 51.8},
    #                             'bottomRight': {'x': 1905.408, 'y': 1120.8},
    #                             'bottomLeft': {'x': 525.4, 'y': 1106.4}}}

    count = 0
    while True:
        ret, frame = vid.read()
        if ret:
            begin = time.time()
            app.predict(frame, params)
            print(f"cable algorithm 处理 1 帧 img cost time: {time.time() - begin}s...")
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
            count += 1
        else:
            break
