%Hough detection
clear; %清除上次运行的所有变量
close all; %关闭上次运行的子窗口

%=====下面读取原图并显示
Gray = imread('line.bmp');
if ndims(Gray) == 3
    Gray = rgb2gray(Gray);
end
figure(1),imshow(Gray) %将图像显示出来
Image = im2double(Gray);%将图片的数据类型从unit8变为double型，只有这样回叙才能进行处理


%=====下面进行Sobel方法的边缘提取并显示
I_edge = edge(Image,'canny'); %边缘提取，采用Sobel方法
figure(2),imshow(I_edge) %将结果图像显示出来


%=====输入源图像大小
[image_y_max, image_x_max] =  size(Image);

% y = a*cosh((x- b)/a) + c
a_initial = 400; % a = a_initial + k * a_step
a_step = 1;
a_range = 45; 
m = round(a_range / a_step+1);%第一个变量的维数

b_initial = 350;
b_step = 1;
b_range = 20;
n = round(b_range /b_step + 1);%第二个变量的维数

c_initial = -440;
c_step = 1;
c_range = 20;
o = round(c_range/c_step + 1);%第三个变量的维数

%=====初始化hough投票矩阵
M_hough=zeros(m,n,o);

%=====对每个像素操作
for x = 1 : image_x_max - 1
    for y = 1 : image_y_max - 1
        %==显示坐标系为y轴向下，转换为y轴向上
        u = -y + image_y_max; 
        v = x;
        %=====如果有点，就投票
        if I_edge(u,v) == 1
            for i = 1 : m-1
            %=====计算a
                a = a_initial + i*a_step;
                for j = 1 : n-1 
                    b = b_initial + j * b_step;
                    c = u - a*cosh((v - b)/a);
                    c = round(c - c_initial);
                    if (c >=1) && (c <= o-1)
                        M_hough(i,j,c) = M_hough(i,j,c) + 1;
                    end
                end
            end
        end
    end
end



%=====显示M_hough矩阵
%figure(3),mesh(M_hough);


% %======取出最大值所在的行、列

[max_val, position_max] = max(M_hough(:)); 
[am,bm,cm] = ind2sub(size(M_hough),position_max);

 a_line = a_initial + am * a_step;
 b_line = b_initial + bm * b_step;
 c_line = c_initial + cm;
 for  x = 1 : image_x_max  - 1
    y = a_line*cosh((x - b_line)/a_line) + c_line;
    if (y >=1) && (y <= image_y_max - 1)
        v = x ;
        u = -y + image_y_max;
        u = round(u);
        Image(u,v)  = 255;
    end
 end
 
 figure(3),imshow(Image);
