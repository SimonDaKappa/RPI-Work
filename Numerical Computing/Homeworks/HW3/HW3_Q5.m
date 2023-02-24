f = @(x) x.^2 - 3;
xc = solveEquationBySecant(f,0,2,1e-12,20)

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

xb1 = solveEquationBySecant(b,1,2, 1e-12, 20)
xb2 = solveEquationBySecant(b,4,5, 1e-12, 20)
xb3 = solveEquationBySecant(b,9,8, 1e-12, 20)





