function [x,iter] = jacobi(A,b,maxIt,tol)
    n = length(b);
    D = diag(diag(A));
    D_inv = inv(D);
    [L,U] = luFactorNoPivoting(A);
    % Strip diagonal from L and U
    for i=1:n
        for j=1:n
            if i == j
                L(i,j)=0;
                U(i,j)=0;
            end
        end
    end
    x0 = zeros(n,1);
    x = x0;
    RBE = norm(A*x0-b, "inf")/norm(b,"inf");
    iter = 0;
    while RBE > tol
        % Main iteration
        if iter > maxIt
            x
            error('max iterations exceeded.')
        end
        iter = iter + 1;
        xold = x;
        for i  = 1:n
            sigma = 0;
            for j = 1:n
                if j ~= i
                sigma = sigma + A(i,j)*xold(j);
                end
            end
            x(i) = (b(i)-sigma)/A(i,i);
        end
        % Data output
        RBE_old = RBE;
        RBE = norm(A*x-b, "inf")/norm(b,"inf");
        if( mod(iter,10) == 1 )
            ratio = RBE/RBE_old;
            name = 'Jacobi';
            fprintf('%s: k=%5d, delta=%8.2e, CR=%8.2e\n',name,iter,RBE,ratio)
        end
    end
x;
end