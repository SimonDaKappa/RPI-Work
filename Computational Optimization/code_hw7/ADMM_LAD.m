function [x,hist_obj, out] = ADMM_LAD(A,b,rho,tol,maxit,x0)

% alternating direction method of multipliers for
% min_x ||A*x-b||_1

[m,n] = size(A);

% initialization
x = x0;
z = A*x - b;

hist_obj = norm(z,1);

% initialize the multiplier
y = zeros(m,1);

pr = 0;
dr = 1;

iter = 1;
while max(pr,dr) > tol & iter < maxit
    iter = iter + 1;
    
    % update x

    
    % update z 
    z0 = z;

    
    % update y
    
    % compute primal and dual residual
    pr = ;
    dr = ;
    
    % compute and save objective value ||A*x-b||_1
    obj = ;
    hist_obj = [hist_obj; obj];
    
end
out.iter = iter;
out.pr = pr;
out.dr = dr;
end