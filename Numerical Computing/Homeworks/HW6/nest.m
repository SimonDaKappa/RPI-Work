%Input: degree d of polynomial,
% array of d+1 coefficients c (constant term first),
% x-coordinate x at which to evaluate, and
% array of d base points b, if needed
function y= nest(d,c,x,b)
  if nargin<4, b=zeros(d,1); end
  y=c(d+1);
  for i=d:-1:1
    y = y.*(x-b(i))+c(i);
  end
end