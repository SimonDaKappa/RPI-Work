function [x,iter] = SOR(A,b, w,maxIt,tol)
    n = length(b);
    x_0 = zeros(n,1);
    D = diag(diag(A));
    L =-tril(A,-1);
    U = -triu(A,1);
    a = (D-w*L);
    RBE = norm(A*x_0-b, "inf")/norm(b,"inf");
    iter = 0;
    while RBE > tol
        if iter > maxIt
            x;
            error('max iterations exceeded')
        end
        iter = iter + 1;
        % Update Scheme
        x = a\(((1-w)*D + w*U)*x_0) + w*(a\b);
        x_0 =  x;
        % Output Formatting
        RBEOld = RBE;
        RBE = norm(A*x-b,"inf")/norm(b,"inf");
        if( mod(iter,10) == 1 )
            fprintf(' %s: k=%5d, delta=%8.2e, CR=%8.2e\n','SOR',iter,RBE,RBE/RBEOld);
        end
    end
    x;
end
