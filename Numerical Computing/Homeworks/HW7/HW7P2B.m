A = [1 -2;1 0;1 1;1 2];
b = [log(1);log(2);log(2);log(5)];
ATA = A.'*A;
ATb = A.'*b;
xbar = ATA\ATb
RMSE = norm(b-A*xbar)\sqrt(length(b))

c1 = exp(xbar(1));
x = linspace(-2,2,101);
f = @(x)  c1*exp(xbar(2)*x);
plot(x,f(x),'b',[-2;0;1;2],[1;2;2;5],'r*')