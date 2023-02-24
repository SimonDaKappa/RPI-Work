f = @(x) 1./(1+2*x.^2);
a = -2; b = 2; n = 21;

% Polynomial 
xd = linspace(a,b,n);
yd = f(xd);
x = linspace(a,b,201);
yF = f(x);
yI = polyInterp(xd,yd,x);
figure
plot(x,yF,'b',x,yI,'g--',xd,yd,'r*')
legend('Function Eval', 'Interpolating Polynomial','Data Points')
xlabel('x')
ylim([-1, 2])
ylabel('y')
title([num2str(n) ' Data Point Polynomial Interpolation'])
figure
plot(x,yF-yI)
title([num2str(n) ' Data Point Interpolation Error'])
xlabel('x')
ylabel('y')
legend('E(x) = f(x) - P(x)')

% Chebyshev
xd = zeros(n,1);
for i = 1:n
  xd(i) = (b-a)/2*cos((2*i-1)*pi/(2*n))+(b+a)/2;
end
yd = f(xd);
x = linspace(a,b,201);
yF = f(x);
yI = polyInterp(xd,yd,x);
figure
plot(x,yF,'b',x,yI,'g--',xd,yd,'r*')
legend('Function Eval', 'Interpolating Polynomial','Data Points')
xlabel('x')
ylim([-1, 2])
ylabel('y')
title([num2str(n) ' Data Point Chebyshev Interpolation'])
figure
plot(x,yF-yI)
title([num2str(n) ' Data Point Chebyshev Interpolation Error'])
xlabel('x')
ylabel('y')
legend('E(x) = f(x) - P(x)')
