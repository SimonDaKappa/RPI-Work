function [x, iter] = gauss_seidel(A,b,maxIt,tol)
    n = length(b);
    x0 = zeros(n,1);
    x = x0;
    RBE = norm(A*x0-b, "inf")/norm(b,"inf");
    iter = 0;
    while RBE > tol
        if iter > maxIt
            x 
            error('max iterations exceeded')
        end
        iter = iter+1;
        xold = x;
        for i=1:n
            sigma=0;
            for j=1:i-1
                sigma=sigma+A(i,j)*x(j);
            end
            for j=i+1:n
                sigma=sigma+A(i,j)*xold(j);
            end
        x(i)=(1/A(i,i))*(b(i)-sigma);        
        end
        RBEOld = RBE;
        RBE = norm(A*x-b,"inf")/norm(b,"inf");
        if( mod(iter,10) == 1 )
            fprintf(' %s: k=%5d, delta=%8.2e, CR=%8.2e\n','Gauss-Seidel',iter,RBE,RBE/RBEOld);
        end
    end
    x;
end
