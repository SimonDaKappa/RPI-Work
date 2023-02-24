% Find an approximate solution to a system of equations
% f(x)=0
% by Newton’s method
%
% f (input) : vector function f(x)
% fx (input) : function that determines the Jacobian matrix: fx(x)
% x0 (input) : initial guess
% tol (input) : convergence tolerance
% xc (output) : approximate solution
function xc = solveSystemByNewton( f,fx,x0,tol )
    k = 0;
    xc = [x0];
    backerror = norm(f(x0),"inf");
    while backerror > tol
        if k == 0
            xprev = x0;
        else
            xprev = xc(:,k+1);
        end
        x = xprev - fx(xprev)^(-1)*f(xprev);
        xc = [xc , x];
        k = k + 1;
        backerror = norm(f(x),"inf");
        fprintf('solveSystemByNewton: it=%d: x=[%12.6e',k,x(1));
        for j=2:size(x)
            fprintf(',%12.6e',x(j)); 
        end
        fprintf('] ||f(x)||_inf=%8.2e\n',norm(f(x),inf));
    end
    
end
