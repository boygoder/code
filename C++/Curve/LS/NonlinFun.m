function result = NonlinFun(t)
a = t(1); b = t(2); c = t(3);                               % 待拟合的参数
result = y_real - ( a*cosh( (x_real-b)/a ) + c);                               % 返回拟合结果
end
