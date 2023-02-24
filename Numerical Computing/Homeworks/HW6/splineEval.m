%
% Evaluate the spline y=S(x) and its derivative yx=S’(x)
%
% xs,ys,coeff (input) : spline data from splineCoeff
% x (input) : evaluate the spline at these points
% y (output) : array of evaluated spline values
% yx (output) : array of spline first derivatives
%
function [y,yx] = splineEval( xs,ys,coeff,x )
y = [];
yx = [];
n1 = length(x);
n2 = length(xs) - 1;
for i = 1:n1
  for j = 1:n2
    %fprintf("(i,j) = (%1d,%1d) | x(i) = %2.4f, xs(j+1) = %2.4f\n",i,j,x(i),xs(j+1))
    if x(i) <= xs(j+1)
      y(i) = ys(j) + coeff(j,1)*(x(i)-xs(j))+coeff(j,2)*(x(i)-xs(j))^2;
      yx(i) = coeff(j,1) + 2*coeff(j,2)*(x(i)-xs(j));
      break
    end
    if x(i) > xs(n2)
      y(i) = ys(n2) + coeff(n2,1)*(x(i)-xs(n2))+coeff(n2,2)*(x(i)-xs(n2))^2;
      yx(i) = coeff(n2-1,1) + 2*coeff(n2,2)*(x(i)-xs(n2));
    end
  end
end

end