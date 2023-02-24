% RK4 (Runge-Kutta, 4th order accurate) scheme to solve
% y’ = f(t,y) for a <= t <= b
% y(a)=ya
% Input parameters:
% f : slope function
% a,b : time interval
% ya : initial condition
% nstep : number of steps to take
% Output:
% t(i), i=1,2,..., nstep+1 : solution is computed at these times.
% y(:,i) i=1,2,..., nstep+1 : approximate solution
function [t,y] = RK4( f, a, b, ya, nstep )
  h = (b-a)/nstep;
  t = linspace(a,b,nstep+1);
  y(:,1) = ya;
  for i=1:nstep
    yi = y(:,i);
    ti = t(i);
    k1 = f(ti,yi);
    k2 = f(ti+h/2,yi+h*k1/2);
    k3 = f(ti+h/2,yi+h*k2/2);
    k4 = f(ti+h,yi+h*k3);
    y(:,i+1) = yi + 1/6*(k1+2*k2+2*k3+k4)*h;
  end
end