function [] = lsq(file_path,file_name,file_ext)

    %=====下面读取原图并显示
    file  = strcat(file_path,file_name,file_ext);
    Gray = imread(file);
    if ndims(Gray) == 3
        Gray = rgb2gray(Gray);
    end
    figure(1),imshow(Gray) %将图像显示出来
    Image = im2double(Gray);%将图片的数据类型从unit8变为double型
    %=====输入源图像大小
    [image_y_max, image_x_max] =  size(Image);
    fprintf('原图片高度：%d,原图片宽度：%d\n',image_y_max,image_x_max);
   
        %对图片进行裁剪，只取包含曲线的部分
    min_x = 1;
    max_x = 1;
    min_y = 1;
    max_y = 1;
    sum_col = sum(Image,1);
    for i = 1 : image_x_max
        if (sum_col(i) ~= 0)
            min_x = i;
            break;
        end
    end
    for i = image_x_max : -1 : min_x + 1
        if (sum_col(i) ~= 0)
            max_x = i;
            break;
        end
    end

    sum_row = sum(Image,2);
    for i = 1 : image_y_max
        if (sum_row(i) ~= 0)
            min_y = i;
            break;
        end
    end
    for i = image_y_max : -1 : min_y + 1
        if (sum_row(i) ~= 0)
            max_y = i;
            break;
        end
    end

    Image = Image(min_y:max_y, min_x:max_x);
    fprintf('min_x:%d,max_x:%d,min_y:%d,max_y:%d\n',min_x,max_x,min_y,max_y);
    [image_y_max, image_x_max] =  size(Image);
    fprintf('裁剪后长度:%d，裁剪后宽度:%d\n',image_y_max,image_x_max);
    figure(2),imshow(Image);
    cut= strcat(file_path,file_name,'_cut');
    print('-dpng' , '-r200' , cut);
    
    %将曲线宽度降为1像素
    for x  =  1 : image_x_max 
        white = false;
        for y =  image_y_max :-1 : 1
            v = x;
            u = -y + image_y_max + 1;
            if (Image(u,v) == 1)
                if (white == false)
                    white = true;
                else
                    Image(u,v) = 0;
                end
            else
                white = false;
            end
        end
    end
    figure(3),imshow(Image)


    %根据每列的和判断是否有交点，我们希望截取一段无交点部分(最长的部分)
    count = zeros(image_x_max,1);
    for i =  1 : image_x_max
        count(i) = sum(Image(:,i)~=0);
    end
    %判断有几条曲线，选择能够提供充分样点的最大曲线。（抛弃那些孤儿点）
    num_curve = max(count);
    num_curve_cut = find(count == num_curve);
    length = size(num_curve_cut);
    min_length = round(image_x_max/20);
    while (length < min_length)
        count(num_curve_cut) = 0;
        num_curve = num_curve - 1;
        num_curve_cut = find(count == num_curve);
        length = size(num_curve_cut);
    end
    
    fprintf('判定缆绳数量为：%d',num_curve);
        
    length = 1;
    i = 1;
    while  ( i < image_x_max ) && ( count(i) ~= num_curve )
        i = i + 1;
    end
    share_index = i;
    for j = i+1 : image_x_max
        while ( j <= image_x_max) && ( count(j) == num_curve)
            j = j + 1;
        end
        sublength = j - i;
        if (sublength > length)
            length = sublength;
            share_index = i;
        end
        i = j + 1;
        while (i <= image_x_max) && ( count(i) ~= num_curve )
            i = i + 1;
        end
        j = i + 1;
    end

    fprintf('截取起点：%d, 截取长度：%d\n',share_index,length);




    

       %注意此处，share_index + length -1 才是终点，不然会多取一个
    Image_cut  = Image( : , share_index : share_index + length - 1);
    figure(4),imshow(Image_cut);
    [imagecut_y_max,imagecut_x_max] = size(Image_cut);

    %截取初始用来回归的点
    Curves = zeros(imagecut_x_max,2,num_curve);
    for x =  1 : imagecut_x_max
        curve_id = 0;
        for y =  imagecut_y_max : -1 : 1
            v = x + share_index - 1;
            u = -y + imagecut_y_max + 1;
            if (Image_cut(u,x) == 1)
                curve_id  = curve_id + 1;
                Curves(x,1,curve_id) = v;
                Curves(x,2,curve_id) = y;
            end
        end
    end
    %disp(Curves(1,1,:))

    parameter_origin = zeros(num_curve,3);
    for i = 1 : num_curve
            fun = @(t)( t(1)*cosh( (Curves(:,1,i)-t(2))./t(1) ) + t(3) - Curves(:,2,i));
            parameter_initial = [imagecut_y_max,imagecut_x_max,-imagecut_y_max];                              % 待辨识参数的初值
            parameter_origin(i,:) = lsqnonlin(fun,parameter_initial);               % 非线性拟合
    end

    figure(5),imshow(Image),hold on
    for id  =  1 : num_curve
        t = parameter_origin(id,:);
        x_fit = zeros(image_x_max,1);
        y_fit = zeros(image_x_max,1);
        for x = 1 : image_x_max
            x_fit(x) = x;
            y_fit(x) = t(1)*cosh((x - t(2))./ t(1)) + t(3);
        end
        u_fit = - y_fit + image_y_max;
        plot(x_fit,u_fit,'LineWidth',2,'Color','green');
        hold on
    end
    
    
    
    [parameter,CurvesFinal] = CalculateParameter(Image,Curves,parameter_origin,num_curve,6);
    for id = 1 : num_curve
        a = parameter(id,1);
        b = parameter(id,2);
        c = parameter(id,3);
        fprintf('y = %f*cosh((x- %f)/%f) + %f \n',a,b,a,c);
    end
    
    
    radian = zeros(num_curve,1);
    for id = 1: num_curve
            curve_x = CurvesFinal(:,1,id);
            curve_y = CurvesFinal(:,2,id);
            %将曲线中没有选定点的列删除。
            zero_column = find(curve_y == 0);
            curve_x(zero_column) = [];
            curve_y(zero_column) = [];
            
            %取出样本点的起点和终点，画出直线。
            pnt_num = size(curve_x,1);
            x_start = curve_x(1);
            y_start = curve_y(1);
            x_end = curve_x(pnt_num);
            y_end = curve_y(pnt_num);
            
            %起点到终点的直线。
            k = (y_end - y_start) / (x_end - x_start);
            b = y_end - k * x_end;
            

            
            %计算曲线到直线的距离，取出最大值计算弯曲度
            line_length  = sqrt(power(x_end - x_start,2) + power(y_end - y_start,2));
            distance = zeros(pnt_num,1);
            for i =  1 : pnt_num
                distance(i) = abs(k*curve_x(i) - curve_y(i) + b) / sqrt(1 + k*k);
            end
            max_distance = max(distance);
            radian(id) = max_distance / line_length;
            fprintf('y = %f x + %f ',k,b);
    end
    
    disp(radian);
    figure(5),imshow(Image),hold on
    for id  =  1 : num_curve
        t = parameter(id,:);
        x_fit = zeros(image_x_max,1);
        y_fit = zeros(image_x_max,1);
        for x = 1 : image_x_max
            x_fit(x) = x;
            y_fit(x) = t(1)*cosh((x - t(2))./ t(1)) + t(3);
        end
        u_fit = - y_fit + image_y_max;
        plot(x_fit,u_fit,'LineWidth',2,'Color','green');
        hold on
    end
    
    fig= strcat(file_path,file_name,'_fit');
    print('-dpng' , '-r200' , fig);
    para_save = strcat('./parameter/',file_name,'_parameter.txt');
    para = fopen(para_save,'wt');
    fprintf(para,'%20s %20s %20s %20s \r\n','a','b','c','radian');
    for i = 1 : num_curve
        fprintf(para, '%12.8f %12.8f %12.8f', parameter(i, :));
        fprintf(para, '%12.8f \r\n',radian(i));
    end
    fclose(para);
end

