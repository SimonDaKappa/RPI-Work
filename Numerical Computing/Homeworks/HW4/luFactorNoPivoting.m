function [L,U] = luFactorNoPivoting(A)
    sz = size(A);
    n = sz(1); 
    L = eye(n);
    U = A;
    for j = 1:n-1
        for i = j+1:n
            L(i,j) = U(i,j)/U(j,j);
            U(i,j:n) = U(i,j:n) - L(i,j)*U(j,j:n);
        end
    end
end