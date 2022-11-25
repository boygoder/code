clear;
close all;

% for f=  3 : 3
%     file_path = '.\figure\';
%     file_name = int2str(f);
%     file_ext = '.png';
%     file  = strcat(file_path,file_name,file_ext);
%     Gray = imread(file);
%     BW = edge(Gray,'sobel');%sobel
%     figure,imshow(BW);
%     clear; %清除上次运行的所有变量
% %     close all; %关闭上次运行的子窗口
% end   
pnt = zeros(10,2,3)
s = size(pnt,1)
