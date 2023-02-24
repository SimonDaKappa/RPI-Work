% Compute an approximation to a definite integral of f
% using the composite Simpson’s rule.
% f (input) : function to integrate
% [a,b] : interval of integration
% m : number of panels
% sum (output) : approximation to the integral
function sum = compositeSimpson(f,a,b,m)
  h = (b-a)/m;
  sum_odd = 0;
  sum_even = 0;
  for j=1:m-1
    x(j) = a+j*h;
    y(j) = f(x(j));
    if rem(j,2) == 1 % j odd
      sum_odd = sum_odd + y(j);
    else
      sum_even = sum_even + y(j);
    end
  end
  sum = h/3*(f(a) + f(b) + 4 *sum_odd + 2*sum_even);
end