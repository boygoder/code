clear;
close all;

%for f=  1 : 15 
    file_path = '.\figure\';
    file_name = '3';%int2str(f);
    file_ext = '.png';
    lsq(file_path,file_name,file_ext);
    clear; %清除上次运行的所有变量
    %close all; %关闭上次运行的子窗口
%end