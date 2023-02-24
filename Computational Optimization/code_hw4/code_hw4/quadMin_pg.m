function [x, hist_obj] = quadMin_pg(A,b,x0,maxit,lb,ub)

% projected gradient method for solving
% min_x 0.5*x'*A*x - b'*x
% s.t. lb <= x <= ub
x = x0;

% compute gradient of the objective
grad = A*x-b;

% compute the Lipschitz constant of grad
L = norm(A);

hist_obj = .5*(x'* (grad - b));

for iter = 1:maxit
    % update x by projected gradient with step size 1/L
    inner = x - (1/L)*(grad);
    x = max(lb, min(ub, inner));
    
    % compute gradient of the objective
    grad = A*x-b;
    
    % save objective value
    hist_obj = [hist_obj; .5*(x'* (grad - b))];
    
end

end

