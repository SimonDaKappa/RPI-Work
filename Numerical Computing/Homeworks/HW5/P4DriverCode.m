f = @(x) [x(1)^2 + x(2)^2 - 1; (x(1)-1)^2 + x(2)^2 - 1];
fx = @(x) [ 2*x(1), 2*x(2); 2*(x(1)-1), 2*x(2)];
disp("x = [1;1]")
xc = solveSystemByNewton(f,fx,[1;1],1e-10);
disp("x = [-1;-1]")
xc2 = solveSystemByNewton(f,fx,[-1;-1],1e-10);
