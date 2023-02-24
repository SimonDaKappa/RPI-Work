x = -1:0.05:1;
f = @(x) cos(3*x) + tanh(x);
y = f(x);
plot(x,y)
grid on
xlabel('x')
ylabel('f(x)')