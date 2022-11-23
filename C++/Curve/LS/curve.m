%Hough detection
clear; %清除上次运行的所有变量
close all; %关闭上次运行的子窗口

%=====下面读取原图并显示
Gray = imread('3.bmp');
if ndims(Gray) == 3
    Gray = rgb2gray(Gray);
end
figure(1),imshow(Gray) %将图像显示出来
I2 = im2double(Gray);%将图片的数据类型从unit8变为double型，只有这样回叙才能进行处理


%=====下面进行Sobel方法的边缘提取并显示
I_edge = edge(I2,'sobel'); %边缘提取，采用Sobel方法
figure(2),imshow(I_edge) %将结果图像显示出来


%=====输入源图像大小
[image_y_max, image_x_max] =  size(I2);




%=====输入搜索初始角度
alpha_initial = -90;

%=====输入搜索步长角度
thelta_step = 1;

%=====输入搜索总角度范围
total_angle_for_search = 180;
m = round(total_angle_for_search/thelta_step+1);

%=====初始化hough投票矩阵，为防止计算的lamda距离超出矩阵，设置一个大的矩阵
n=5000;
M_hough=zeros(n,m);

%=====防止距离为负，搜索初始距离
lamda_initial =round(n/2);%()

%=====对每个像素操作
for x = 1 : image_x_max - 1
    for y = 1 : image_y_max - 1
        %=====转换为矩阵下标的坐标系
        u = -y + image_y_max; %实际y轴正向向上。
        v=x;
        %=====如果有点，就投票
        if I_edge(u,v) == 1
        %======循环m次，直线旋转投票
            for k = 1 : m-1
            %=====计算角度
                alpha1 = alpha_initial + k*thelta_step;
                alpha1 = round(alpha1);

                %=====计算距离
                lamda1 = x*cos(alpha1*pi/180)+y*sin(alpha1*pi/180); %角度转弧度
                lamda1 = round(lamda1);
                M_hough(lamda_initial + lamda1,k) = M_hough(lamda_initial + lamda1,k) + 1;
            end
        end
    end
end



%=====显示M_hough矩阵
figure(3),mesh(M_hough);


%======取出最大值所在的行、列
[rm,km]=find(M_hough == max(max(M_hough)));

%=====计算该点原距离
rm = rm - lamda_initial;
%draw the line

%=====计算该点原角度
alpha_line = alpha_initial + km*thelta_step;
alpha_line_rad = alpha_line*pi/180;
lamda_line = rm/sin(alpha_line_rad);


%I = zeros(image_y_max,image_x_max);
%  % =====在原图像上重叠画出该直线
for x=1:image_x_max-1
    %=====直线方程式
    y = -x*(1/tan(alpha_line_rad))+lamda_line;
    %=====只画在图像中的直线
    if y <= image_y_max - 1
        if y >= 1
            v = x;
            u = -y + image_y_max; %转换为实际坐标
            u = round(u);
            I2(u,v) = 255;%画白色线
        end
    end
end
% 
% 
% 
% %=====显示检测结果
% 

figure(4),imshow(I2);