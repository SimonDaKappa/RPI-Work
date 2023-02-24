%
% Find an approximate solution to a scalar equation
% f(x)=0
% by the Secant Method.
%
% f (input) : function f(x)
% x0,x1 (input) : initial guesses
% tol (input) : convergence tolerance
% xc (output) : approximate solution
% maxIterations (input) : maximum number of kations
function [xc] = solveEquationBySecant( f,x0,x1,tol,maxIt)
k = 0;
xc = x1 - f(x1)* (x1-x0)/(f(x1)-f(x0));
xhist = [x0,x1,xc];
fc = f(xc);
fhist = [f(x0),f(x1),fc];
res = abs(fc);

while res > tol
    k = k + 1;
    if k > maxIt
        disp('Max Iterations Exceeded')
        xc = Inf;
        return
    end
    
    % Update x_k
    xc = (xhist(k+1)*fhist(k+2)-xhist(k+2)*fhist(k+1))/(fhist(k++2)-fhist(k+1));
    xhist = [xhist, xc];
    
    % Update f(x_k)
    fc = f(xc);
    fhist = [fhist, fc];

    ratio = fhist(k+3) / fhist(k+2);
    p = log(abs( fhist(k+3) / fhist(k+2) )) / log(abs( fhist(k+2) / fhist(k+1) ));
    fprintf('Secant: it=%2d: x=%13.6e f(x)=%9.2e ratio=%9.2e p=%4.2f\n',k,xc,fc,ratio,p);
    res = abs(fc);
end
end
