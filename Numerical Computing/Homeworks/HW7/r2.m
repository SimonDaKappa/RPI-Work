function error = r2(x)
  data = [1 8;2 12.3;3 15.5;4 16.8; 5 17.1; 6 15.8;7 15.2;8 14.0];
  m = length(data);
  error = zeros(m,1);
  for i=1:m
    error(i) = x(1)*data(i,1)*exp(x(2)*data(i,1))-data(i,2);
  end
end