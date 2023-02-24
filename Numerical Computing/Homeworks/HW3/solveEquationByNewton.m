%
% Find an approximate solution to a scalar equation
% f(x)=0
% by Newton’s method
%
% f (input) : function f(x)
% fx (input) : function that defines f’(x)
% x0 (input) : initial guess
% tol (input) : convergence tolerance
% xc (output) : approximate solution
% maxIterations (input) : maximum number of iterations
function [xc] = solveEquationByNewton( f, fx , x0, tol, maxIt )

iter = 0;
xc = x0 - f(x0)/fx(x0);
fc = f(xc);
res = abs(fc);
xhist= [x0,xc];
fhist = [f(x0), fc];
while res > tol 
    
    iter = iter + 1;
    if iter > maxIt
        disp('Max Iterations Exceeded!\n')
        xc = Inf;
        return
    end

    
    % Update f(x_k)
    fc = f(xhist(iter + 1));
    fxc = fx(xhist(iter + 1));
    % Update x_k
    xc = xhist(iter + 1) -  fc/fxc;
    xhist = [xhist, xc];
    % Update fx_k
    fc = f(xc);
    fhist = [fhist, fc];
    res = abs(fc);
    % Output Formatting
    ratio = fc/fhist(iter + 1);
    if( iter==1 ) % do not print p first time
        fprintf('Newton: iter =%2d: x =%13.6e f(x) =%9.2e ratio =%9.2e\n',iter,xc,fc,ratio);
    else
        p = log(abs(fc/fhist(iter+1)))/log(abs(fhist(iter + 1)/fhist(iter)));
        fprintf('Newton: iter =%2d: x =%13.6e f(x) =%9.2e ratio =%9.2e p =%4.2f\n',iter,xc,fc,ratio,p);
    end     
end
end
