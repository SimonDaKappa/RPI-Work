% Compute a fixed point g(x)=x
% g (input) : function to use
% x0 (input) : initial guess
% tol (input) : convergence tolerance
% maxIt (input) : maximum number of iterations
% xc (output) : approximation to the fixed point
function xc = fixedPoint(g,x0,tol,maxIt)

iter = 0;
xc = x0;
gx = g(x0);
res = abs(gx - x0);

while res > tol
    iter = iter + 1;
    if iter > maxIt
        disp("Max Iterations Exceeded!")
        xc = Inf;
        return
    end
    xOld = xc;

    % Actual Iteration 
    gx = g(xc);
    xc = gx;

    % Error
    res = abs(xc-xOld);

    fprintf('fixedPoint: k=%2d xc=%18.12e |xc-xOld|=%8.2e\n',iter,xc,abs(xc-xOld))

    


end



end
