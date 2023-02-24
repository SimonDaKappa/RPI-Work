function M = p3matrix(n)
M = zeros(n,n);
for i = 1:n
    for j = 1:n
        M(i,j) = abs(i-j) + 1;
    end
end