function [x, hist_res] = quadMin_gd(A,b,x0,tol)

% steepest gradient method for solving
% min_x 0.5*x'*A*x - b'*x

% get the size of the problem
n = length(b);

x = x0;

% compute gradient of the objective
grad = A*x-b;

% evaluate the norm of gradient
res = norm(grad);

% save the value of res
hist_res = res;

while res > tol
    
    % find descent direction p
    p = -grad;
    
    % compute the stepsize alpha by exact line search
    alpha = (norm(-grad)^2)/(p.' * A * p);
    
    % update x
    x = x + alpha * p;
    
    % compute gradient of the objective
    grad = A*x-b;
    
    % evaluate the norm of gradient
    res = norm(grad);
    
    % save the value of res
    hist_res = [hist_res; res];
end

end

