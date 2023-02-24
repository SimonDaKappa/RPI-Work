f = @(x) x.^2-17;
fx = @(x) 2*x;

xc = solveEquationByNewton(f,fx,1,1e-12,20)

b = @(x) besselj(2,x);
bx = @(x) 1/2 * (besselj(1,x) - besselj(3,x));

X = -2:0.1:10;
B = b(X);
plot(X,B)
grid on
legend('J_2')
title('Bessel Function of the First Kind (Scalar)')
xlabel('x')
ylabel('J_2(x)')
x_start = 1;
xb1 = solveEquationByNewton(b,bx,x_start,1e-12,20)
x_start = 4;
xb2 = solveEquationByNewton(b,bx,x_start,1e-12,20)
x_start = 9;
xb3 = solveEquationByNewton(b,bx,x_start,1e-12,20)
