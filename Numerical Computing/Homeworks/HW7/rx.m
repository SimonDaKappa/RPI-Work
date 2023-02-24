function Derror = rx(x)
  data = [0 53.05;5 73.04;10 98.31;15 139.78;20 193.47;25 260.20;30 320.39];
  [m,n] = size(data);
  Derror = zeros(m,2);
  for i = 1:m
    Derror(i,1) = -exp(x(2)*data(i,1));
    Derror(i,2) = -x(1)*data(i,1)*exp(data(i,1)*x(2));
  end
end