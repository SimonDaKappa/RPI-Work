%
% Calculate spline coefficients (see textbook)
%
% xs,ys (input) : x and y coordinates of the spline data
% bcLeft, gLeft (input): boundary condition option and value on the left side, x=a.
% bcLeft = 0 : natural boundary condition (gLeft not used)
% bcLeft = 1 : clamped boundary condition, set S’(a)=gLeft
% bcLeft = 2 : curvature boundary condition, set S’’(a)=gLeft
% bcRight, gRight (input): boundary condition option and value on the right side, x=b.
% bcRight = 0 : natural boundary condition (gRight not used)
% bcRight = 1 : clamped boundary condition, set S’(b)=gRight
% bcRight = 2 : curvature boundary condition, set S’’(b)=gRight
% coeff (output) : spline coefficients
%
function coeff = splineCoeff( xs,ys, bcLeft,gLeft, bcRight,gRight )
n = length(xs);
A = zeros(n,n);
r = zeros(n,1);
for i = 1:n-1
    dx(i) = xs(i+1) - xs(i); dy(i) = ys(i+1)-ys(i);
end
for i=2:n-1 % Load the matrix
    A(i,i-1:i+1)=[dx(i-1) 2*(dx(i-1)+dx(i)) dx(i)];
    r(i)= 3*(dy(i)/dx(i)-dy(i-1)/dx(i-1)); % right-hand side
end
% Set Boundary Conditions
if bcLeft == 0 % Left Natural
    A(1,1) = 1; 
end
if bcRight == 0 % Right Natural
    A(n,n) = 1;
end
if bcLeft == 1 % Left Clamped
    A(1,1:2)=[2*dx(1) dx(1)];r(1)=3*(dy(1)/dx(1)-gLeft);
end
if bcRight ==1 % Right Clamped
    A(n,n-1:n)=[dx(n-1) 2*dx(n-1)];r(n)=3*(gRight-dy(n-1)/dx(n-1));
end
if bcLeft == 2 % Left Curvature
    A(1,1)=2;r(1)=gLeft;
end
if bcRight == 2 % Right Curvature
    A(n,n)=2;r(n)=gRight;
end

% Calculate 
coeff=zeros(n,3);
coeff(:,2)=A\r; % solve for c coefficients
for i=1:n-1 % solve for b and d
    coeff(i,3)=(coeff(i+1,2)-coeff(i,2))/(3*dx(i));
    coeff(i,1)=dy(i)/dx(i)-dx(i)*(2*coeff(i,2)+coeff(i+1,2))/3;
end
coeff=coeff(1:n-1,1:3);
end