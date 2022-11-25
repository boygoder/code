function parameter = CalculateParameter(Image,Curves_origin,parameter_origin,num_curve,iterate_time)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    [image_y_max,image_x_max] = size(Image);
    parameter_old = parameter_origin;
    parameter_new = parameter_origin;
    
    expansion_size = round(image_x_max/iterate_time);
    %步步为营，每次扩展一小部分，确保样点分配到正确的部分。
    
    for time = 1 : iterate_time
        %CurveClassfication = zeros(image_x_max,2,num_curve);
        

        pnt_num = size(Curves_origin,1);
        x_cut_min = Curves_origin(1,1,1);
        x_cut_max = Curves_origin(pnt_num,1,1);
        if (x_cut_min > expansion_size)
            x_cut_min = x_cut_min - expansion_size;
        else
            x_cut_min = 1;
        end
        
        if ( image_x_max - x_cut_max >= expansion_size)
            x_cut_max = x_cut_max + expansion_size;
        else
            x_cut_max = image_x_max;
        end
        
        x_cut_size = x_cut_max - x_cut_min + 1;
        CurveClassfication = zeros(x_cut_size,2,num_curve);
        for c = 1 : num_curve
            for i = 1 : x_cut_size
                CurveClassfication(i,1,c) = i + x_cut_min - 1; 
            end
        end
        for  x  = 1 : x_cut_size
            for y =  image_y_max : -1 : 1
                u = -y + image_y_max + 1;
                v = x + x_cut_min - 1;
                if (Image(u,v) == 1)
                    y_distance = zeros(num_curve,1);
                    abandon = false;
                    for id =  1 : num_curve
                        t = parameter_old(id,:);
                        y_fit = t(1)*cosh((v - t(2))./ t(1)) + t(3);
                        y_distance(id) = abs(y_fit - y);
                    end
                    %寻找离这个点最近的曲线
                    if (~abandon)
                        min_distance = min(y_distance);
                        if (min_distance < 12)
                            curve_id = find(y_distance == min_distance);
                            %CurveClassfication(x,1,curve_id) = v;
                            CurveClassfication(x,2,curve_id) = y;
                        end
                    end
                end
            end
        end

%         for  i  = 1 : image_x_max
%             for j =  image_y_max : -1 : 1
%                 v = i;
%                 u = -j + image_y_max + 1;
%                 if (Image(u,v) == 1)
%                     y_distance = zeros(num_curve);
%                     abandon = false;
%                     for id =  1 : num_curve
%                         t = parameter_old(id,:);
%                         x = i;
%                         y_fit = t(1)*cosh((x - t(2))./ t(1)) + t(3);
%                         y_distance(id) = abs(y_fit - j);
%                     end
%                     %寻找离这个点最近的曲线
%                     if (~abandon)
%                         min_distance = min(y_distance);
%                         if (min_distance < 30)
%                             curve_id = find(y_distance == min_distance);
%                             CurveClassfication(i,1,curve_id) = i;
%                             CurveClassfication(i,2,curve_id) = j;
%                         end
%                     end
%                 end
%             end
%         end

        for id =  1 : num_curve
            curve_x = CurveClassfication(:,1,id);
            curve_y = CurveClassfication(:,2,id);
            %将曲线中没有选定点的列删除。
            zero_column = find(curve_y == 0);
            curve_x(zero_column) = [];
            curve_y(zero_column) = [];

            fun = @(t)( t(1)*cosh( (curve_x-t(2))./t(1) ) + t(3) - curve_y);
            parameter_initial = [image_y_max,image_x_max,-image_y_max];                              % 待辨识参数的初值
            %parameter_initial = [1e6,1e6,-1e6];
            parameter_new(id,:) = lsqnonlin(fun,parameter_initial);               % 非线性拟合

%             % 将拟合结果代入函数
%             x_fit = zeros(image_x_max);
%             y_fit = zeros(image_x_max);
%             for x = 1 : image_x_max
%                 t = parameter_new(id,:);
%                 x_fit(x) = x;
%                 y_fit(x) = t(1)*cosh((x - t(2))./ t(1)) + t(3);
%             end

        %     figure
        %     plot(curve_x,curve_y,'LineWidth',3,'Color','yellow');
        %     hold on
        %     plot(x_fit,y_fit,'LineWidth',3,'Color','red');

        %     u_fit = - y_fit + image_y_max;
        %     plot(x_fit,u_fit,'LineWidth',2,'Color','green');
        %     hold on
        end
        
        parameter_old = parameter_new;
        Curves_origin = CurveClassfication;
    end

    parameter = parameter_new;
end

