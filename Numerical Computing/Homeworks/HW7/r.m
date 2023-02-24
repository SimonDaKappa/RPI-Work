function error = r(x)
  data = [0 53.05;5 73.04;10 98.31;15 139.78;20 193.47;25 260.20;30 320.39];
  [m,n] = size(data);
  error = zeros(m,1);
  for i = 1:m
    error(i) = x(1)*exp(x(2)*data(i,1))-data(i,2);
  end

end