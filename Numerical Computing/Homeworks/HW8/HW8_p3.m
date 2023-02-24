% (a)
f = @(x) 1 + x + x.^2 + x.^3;
sum = compositeSimpson(f,0,1,4)
exact = integral(f,0,1)
%(b)
g = @(x) exp(sin(x.^2));
exact_2 = integral(g,0,pi)
for n = 1:10
   m = 2^n;
   compsim = compositeSimpson(g,0,pi,m);
   error = exact_2 - compsim;
   fprintf('Composite Simpson: m=%4d, sum=%14.8e, error=%9.2e',m,compsim,error);
   if n > 1
     fprintf(' ratio=%5.1f rate=%4.2f\n',error_old/error,log2(error_old/ error));
   else
     fprintf('\n')
   end
   error_old = error;
end