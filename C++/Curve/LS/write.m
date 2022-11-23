% data=[172 179 184 ;
%          184  0 0; 
%          0 0 0];
% d = uint8(data);
% image(d); colormap(gray(8));
% figure(1),imshow(d);

    rotI  = imread('3.bmp');
    BW = edge(rotI,'sobel');%sobel
    [H,T,R] = hough(BW,'Theta',-90:1:89,'Rho',1);
    imshow(H,[],'XData',T,'YData',R,'InitialMagnification','fit');
    xlabel('\theta'), ylabel('\rho');
    axis on, axis normal, hold on;
    P  = houghpeaks(H,3,'threshold',ceil(0.3*max(H(:))));
    x = T(P(:,2)); 
    y = R(P(:,1));
    plot(x,y,'s','color','white');

    % Find lines and plot them
    lines = houghlines(BW,T,R,P,'FillGap',50,'MinLength',100);
    figure, imshow(rotI), hold on
    max_len = 0;
    for k = 1:length(lines)
        xy = [lines(k).point1; lines(k).point2];
        plot(xy(:,1),xy(:,2),'LineWidth',6,'Color','green');

        % plot beginnings and ends of lines
        plot(xy(1,1),xy(1,2),'x','LineWidth',6,'Color','yellow');
        plot(xy(2,1),xy(2,2),'x','LineWidth',6,'Color','red');

        % determine the endpoints of the longest line segment 
        len = norm(lines(k).point1 - lines(k).point2);
        if ( len > max_len)
          max_len = len;
          xy_long = xy;
        end
    end

    % highlight the longest line segment
%plot(xy_long(:,1),xy_long(:,2),'LineWidth',2,'Color','cyan');