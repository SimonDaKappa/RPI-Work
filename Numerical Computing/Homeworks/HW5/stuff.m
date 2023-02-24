disp("Jacobi, green")
M2 = diag(diag(A));
[x2,nit2,rbe2] = preconditionedConjugateGradient(M2,A,b,x0,100,1e-15, 0);

disp("SSOR, w = 1, blue")
[L,U] = lu(A);
D = diag(diag(A));
M3 = (D + L)*D\(D + U);

[x3,nit3,rbe3] = preconditionedConjugateGradient(M3,A,b,x0,100,1e-15, 0);