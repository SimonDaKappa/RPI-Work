% Function to compute and evaluate a polynomial interpolant y=P(x).
% xd,yd (input) : arrays of data points
% x (input) : array of x values at which to evaluate the polynomial
% y (output) : array of values of the polynomial, y=P(x)
function y = polyInterp( xd,yd,x )
  n = length(xd);
  c = newtdd( xd,yd,n );
  y = nest( n-1,c,x,xd );
end
