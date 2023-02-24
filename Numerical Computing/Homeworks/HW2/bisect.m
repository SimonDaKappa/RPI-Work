%Program 1.1 Bisection Method
%Computes approximate solution of f(x)=0
%Input: function handle f; a,b such that f(a)*f(b)<0,
% and tolerance tol
%Output: Approximate solution xc
function xc=bisect(f,a,b,tol, maxIter)
if sign(f(a))*sign(f(b)) >= 0
    error('f(a)f(b)<0 not satisfied!') %ceases execution
end
fa=f(a);
fb=f(b);
iter = 0;
while abs((b-a))/2>tol
    iter = iter + 1;
    if iter > maxIter
        error('Max Iterations Exceeded!') % ceases execution
    end
    c=(a+b)/2;
    fc=f(c);
    if fc == 0 %c is a solution, done
        break
    end
    if sign(fc)*sign(fa)<0 %a and c make the new interval
        b=c;fb=fc;
    else %c and b make the new interval
        a=c;fa=fc;
    end

fprintf('bisect: k=%2d, a=%11.4e f(a)=%8.2e b=%11.4e f(b)=%8.2e c=%14.7e\n',iter,a,fa,b,fb,c);
end

xc=(a+b)/2; %new midpoint is best estimate


end