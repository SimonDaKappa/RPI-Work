function [x, hist_obj, hist_res] = penalty_qp(Q,c,A,b,tol,mu0,mu1,x0)
% quadratic penalty method for the quadratic programming
% min_x 0.5*x'*Q*x - c'*x
% s.t.  x >= 0, A*x == b

mu = mu0;
x = x0;

% compute the residual for the constraint A*x == b
r = max(0,A*x-b);

res = norm(r);
grad_err = 1;
hist_res = res;
hist_obj = 0.5*x'*Q*x - c'*x;

while (res > tol || grad_err > tol) && mu < mu1
    % use constant stepsize
    alpha = 1/norm(Q + mu*A'*A);
    % compute the gradient
    grad = Q*x-b;

    % compute violation of optimality condition
    grad_err = max(0, dot(grad, x-x0));
    while grad_err > tol
        % update x
        x = x - alpha*grad;
        % compute the gradient
        
        grad = A*x-b;
        % compute violation of optimality condition
        grad_err = max(0, dot(grad,x-x0));
    end
    % compute the residual
    r = max(0,A*x-b);
    res = norm(r);
    obj = 0.5*x'*Q*x - c'*x;
    x0=x;
    % save res and obj
    hist_res = [hist_res; res];
    hist_obj = [hist_obj; obj];
    
    % increase the penalty parameter
    mu = 5*mu;
end
end