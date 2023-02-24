function [x, hist_obj] = quadMin_AltMin(A,b,x0,maxit,lb,ub)

% alternating minimization method for solving
% min_x 0.5*x'*A*x - b'*x
% s.t. lb <= x <= ub

x = x0;

% compute the gradient and maintain it
r = A*x - b;

hist_obj = .5*(x'* (r - b));

n = length(b);

for iter = 1:maxit
    
    % update all coordinates cyclicly
    x0 = x;
    for i = 1:n
        % update x(i)

        % Since grad = Ax - b, then x = (b(i) - sum(A(i,j)*x0(j)) ) / A(i,i) 
        % for all j ~= i
        temp = 0;
        for j = 1:n
            if (i ~= j)
                temp = temp + A(i,j) * x(j);
            end
        end
        x(i) = (b(i)-temp)/A(i,i);
    end

    % update r vector in an efficient way
    % quite confused on this part. I do not know how to make this more
    % efficient and I assume this is the major bottleneck for speed of my
    % algorithm
    r = A*x -b;
    
    % save objective value after each cycle
    hist_obj = [hist_obj; .5*(x'* (r - b))];
    
end

end

