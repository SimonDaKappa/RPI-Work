n = 100;
A = zeros(n,n);
x = zeros(n,1);
x0 = x;
for i=1:n
    for j = 1:n
        val = 0;
        if j == i-1
            val = -1;
        end
        if j == i
            val = 1+i;
        end
        if j == i + 1
            val = -1;
        end
        A(i,j) = val;
    end
end
for i = 1:n
    x(i) = n-i+1;
end

b = A*x;
[xGC, nit] = conjugateGradient(A,b,x0,100,1e-5);
xGC;
fprintf('CG: n=%d, rtol=%8.2e, nit=%d max-RFE = %8.2e \n',n,1e-5,nit,norm(x-xGC,'inf')/norm(x,'inf'));

