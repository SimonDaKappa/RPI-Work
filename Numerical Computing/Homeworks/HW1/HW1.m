% Ugly driver script for nest.m
d = 9;
c = [0, 1, 0, -1/3, 0, 2/15, 0, -17/315, 0, 62/2835];
h = 0.25;

p = @(x) x - 1/3*x^3 + 2/15*x^5 - 17/315*x^7 + 62/2835*x^9;
x_NESTED = nest(d,c,h);
x_TANH = p(h);
fprintf('p(%g)=%12.6e (nest), p(%g)=%12.6e (Matlab), diff=%12.6e \n',h,x_NESTED,h,x_TANH,x_NESTED-x_TANH);
fprintf('tanh(%g)=%12.6e \n',h,tanh(h));

a = -1.75; b = 1.75;
x = [];
N = 21;
for i = 1:N
    x = [x, a + (b-a)*(i-1)/(N-1)];
end

y_NESTED = nest(d,c,x);
y_TANH = tanh(x);



figure
plot(x,y_NESTED,'b',x,y_TANH,'r')
title('Nest function results')
xlabel('x')
ylabel('y')
legend('Nested Polynomial','Tanh(x)')
export_fig fig1