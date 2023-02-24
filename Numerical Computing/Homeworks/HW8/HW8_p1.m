f = @(x) exp(x.^2);
d = @(x) 2*x.*exp(x.^2);
d2 = @(x,h) (f(x+h)-f(x-h))/(2*h);
d4 = @(x,h) ( f(x-2*h) - 8*f(x-h) + 8*f(x+h) - f(x+2*h))/(12*h);

x = 1
fx = d(x)
for i  = 1:40
  h(i) = 2^(-i);
  err2(i) = abs(fx - d2(x,h(i)));
  err4(i) = abs(fx-d4(x,h(i)));
end
loglog(h,err2,'b',h,err4,'g')
xlabel('h'); ylabel('error'); title('Approximation Errors')
legend('Second-Order Approximation','Fourth-Order Approximation')
