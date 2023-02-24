function [x, hist_res] = quadMin_pcg(A,C,b,x0,tol)

% conjugate gradient method for solving
% min_x 0.5*x'*A*x - b'*x

% get the size of the problem
n = length(b);

x = x0;

% compute vector r, i.e., gradient of the objective
r = A*x-b;

% set the first p vector 
p = pcg_linsolv(C,-r);
%p = linsolve(C.'*C,-r);
% evaluate the norm of gradient
res = norm(r);

% save the value of res
hist_res = res;

while res > tol
    
    % compute alpha
    
    y = pcg_linsolv(C,r);
    %y = linsolve(C.'*C,r);
    alpha = dot(r,y)/dot(p,A*p);
    
    % update x 
    
    x = x + alpha*p;
    
    % update r
    r_old = r;
    r = r + alpha*A*p;
    
    % compute beta
    y_new = pcg_linsolv(C,r);
    %y_new = linsolve(C.'*C,r);
    beta = dot(r,y_new)/dot(r_old,y);
    
    % obtain the new p vector
    
    p = -y_new + beta*p;
    
    % evaluate the norm of residual vector r
    res = norm(r);
    
    % save the value of res
    hist_res = [hist_res; res];
end

end
