% Homework 2 Driver Code

% Plot f(x) = cos(3x) + 0.5(x^3)
X = -1:.05:1.5;
f = @(x) cos(3*x) + 0.5*x.^3;
y = f(X);
plot(X,y)
grid on
xlabel('x')
ylabel('f(x)')
%a = -1; b = 0;
%xc = bisect(f,a,b,1e-6,100)

%a = .55; b = 1.05;
%xc = bisect(f,a,b,1e-6,100)

%a = .7; b = 1.7;
%xc = bisect(f,a,b,1e-6,100)

% Used for HW3
g = @(x) x.^5 - (10/3)*x.^4 + (40/9)*x.^3 - (80/27)*x.^2+(80/81)*x - (32/243);
a = 0; b = 2;
x_bisect = bisect(g,a,b,1e-16,100);
fprintf('Solution from bisect: x_bisect=%22.16e, f(x_bisect)=%9.2e\n',x_bisect,f(x_bisect));
fprintf('Forward Error: FE = %9.4e, Backward Erorr: BE = %9.4e, Condition Number: kappa = %9.4e\n',abs(x_bisect-3/5),abs(g(x_bisect)),abs(x_bisect-3/5)/abs(g(x_bisect)))
x_fzero = fzero(g,0);
fprintf('Solution from fzero: x_fzero=%22.16e, f(x_fzero)=%9.2e\n',x_fzero,f(x_fzero));
fprintf('Forward Error: FE = %9.4e, Backward Erorr: BE = %9.4e, Condition Number: kappa = %9.4e\n',abs(x_fzero-3/5),abs(g(x_fzero)),abs(x_fzero-3/5)/abs(g(x_fzero)))