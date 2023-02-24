function Derror = rx2(x)
  data = [1 8;2 12.3;3 15.5;4 16.8; 5 17.1; 6 15.8;7 15.2;8 14.0];
  [m,n] = size(data);
  Derror = zeros(m,2);
  for i = 1:m
    Derror(i,1) = -data(i,1)*exp(x(2)*data(i,1));
    Derror(i,2) = -x(1)*data(i,1)^2*exp(data(i,1)*x(2));
  end
end