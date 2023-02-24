n = 500;
A = diag(sqrt(1:n)) + diag(cos(1:(n-10)),10) + diag(cos(1:(n-10)),-10);
x = ones(n,1);
b = A*x;
x0 = zeros(n,1);

disp("Identity, red")
M1 = eye(n);
[x1,nit1,rbe1] = preconditionedConjugateGradient(M1,A,b,x0,500,1e-15, 0);

X1 = uint32(1):uint32(nit1+1);

disp("Jacobi, green")
M2 = diag(diag(A));
[x2,nit2,rbe2] = preconditionedConjugateGradient(M2,A,b,x0,1000,1e-15, 0);
X2 = uint32(1):uint32(nit2+1);



disp("SSOR, w = 1, blue")
[L,U] = lu(A);
D = diag(diag(A));
M3 = (D + L)*D\(D + U);

[x3,nit3,rbe3] = preconditionedConjugateGradient(M3,A,b,x0,2000,1e-15, 0);
X3 = uint32(1):uint32(nit3+1);

semilogy(X1,rbe1,'red',X2,rbe2,'green',X3,rbe3,'blue')
legend('Identity','Jacobi','Gauss Seidel')
title('Relative Backward Error - PCG')
xlabel('Iterations')
ylabel('RBE')