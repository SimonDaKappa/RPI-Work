n = 10
A = full(gallery('tridiag',n,-1,2,-1))
x = zeros(n,1);
for i = 1:n
    x(i) = 11 - i;
end
x
b = A*x
[x_jacobi,iter] = jacobi(A,b,200,1e-4);
RFE = norm(x-x_jacobi, "inf")/norm(x,"inf");
fprintf('%s: RFE = %9.3e, numIterations=%d\n\n','jacobi',RFE,iter-5);

[x_gauss,iter] = gauss_seidel(A,b,100,1e-4);
RFE = norm(x-x_gauss, "inf")/norm(x,"inf");
fprintf('%s: RFE = %9.3e, numIterations=%d\n\n','gauss-seidel',RFE,iter);

[x_sor,iter] = SOR(A,b,1.5,1000,1e-4);
RFE = norm(x-x_sor, "inf")/norm(x,"inf");
fprintf('%s: RFE = %9.3e, numIterations=%d\n\n','SOR',RFE,iter);

for omega = 0.9:.1:2.0
    [x_sor,iter] = SOR(A,b,omega,100,1e-4);
    RFE = norm(x-x_sor, "inf")/norm(x,"inf");
    fprintf('SOR: RFE = %9.3e, omega=%6.3f, numIterations=%3d\n\n',RFE,omega,iter);
end