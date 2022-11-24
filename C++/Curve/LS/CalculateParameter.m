function parameter = CalculateParameter(Image,parameter_origin,num_curve,iterate_time)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    [image_y_max,image_x_max] = size(Image);
    parameter_old = parameter_origin;
    parameter_new = parameter_origin;
    
    for time = 1 : iterate_time
        CurveClassfication = zeros(image_x_max,2,num_curve);
        
        for  i  = 1 : image_x_max
            for j =  image_y_max : -1 : 1
                v = i;
                u = -j + image_y_max + 1;
                if (Image(u,v) == 1)
                    y_distance = zeros(num_curve);
                    abandon = false;
                    for id =  1 : num_curve
                        t = parameter_old(id,:);
                        x = i;
                        y_fit = t(1)*cosh((x - t(2))./ t(1)) + t(3);
                        %如果之前拟合的不好，抛弃
                        if ( y_fit < 1 || y_fit > image_y_max)
                            abandon = true;
                            break;
                        end
                        y_distance(id) = abs(y_fit - j);
                    end
                    %寻找离这个点最近的曲线
                    if (~abandon)
                        min_distance = min(y_distance);
                        %if (min_distance < 5)
                            curve_id = find(y_distance == min_distance);
                            CurveClassfication(i,1,curve_id) = i;
                            CurveClassfication(i,2,curve_id) = j;
                        %end
                    end
                end
            end
        end

        for id =  1 : num_curve
            curve_x = CurveClassfication(:,1,id);
            curve_y = CurveClassfication(:,2,id);
            %将曲线中没有选定点的列删除。
            zero_column = find(curve_x == 0);
            curve_x(zero_column) = [];
            curve_y(zero_column) = [];

            fun = @(t)( t(1)*cosh( (curve_x-t(2))./t(1) ) + t(3) - curve_y);
            parameter_initial = [image_y_max,image_x_max,-image_y_max];                              % 待辨识参数的初值
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
    end

    parameter = parameter_new;
end

