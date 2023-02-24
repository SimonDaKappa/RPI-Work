function y = pcg_linsolv(C,r)


% solve C^T * z = r for z with forward substitution
CT = C.';
n = size(r,1);
z = zeros(n,1);
z(1) = r(1)/CT(1,1);
for i = 2:n
    z(i) = (r(i)-CT(i,1:i-1)*z(1:i-1))./CT(i,i);
end


% solve Cy = z by back substitution
y = zeros(n,1);
y(n) = z(n)/C(n,n);

for i = n-1:-1:1
    y(i) = (z(i)-C(i,i+1:n)*y(i+1:n))./C(i,i);
end

end