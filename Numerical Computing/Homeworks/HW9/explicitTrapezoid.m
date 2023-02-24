% Use the Explicit-Trapezoid scheme to solve
% y’ = f(t,y) for a <= t <= b
% y(a)=ya
% Input:
% f : slope function
% a,b : time interval
% ya : initial condition
% nstep : number of steps to take
%
% Output:
% t(i), i=1,2,..., nstep+1 : solution is given at these times.
% y(:,i) i=1,2,..., nstep+1 : approximate solution
function [t,y,maxerr] = explicitTrapezoid(soln, f, a, b, ya, nstep )
  h = (b-a)/nstep;
  t = linspace(a,b,nstep+1);
  y(:,1) = ya;
  for i = 1:nstep
    soln_y(i+1) = soln(t(i));
    y(:,i+1) = y(:,i) + h/(2)*(f(t(i),y(:,i)) + f(t(i)+h, y(:,i) + h*f(t(i),y(:,i))));
    err(i+1) = soln_y(i)-y(1,i);
  end
  maxerr = max(err);
  % Figure Plotting
  figure
  plot(t,soln_y,'-b.',t,y(1,:),'-g.')
  legend('Actual Y','Approximate Y')
  xlabel('Time t')
  ylabel('Y(t)')
  title([num2str(nstep),'Steps: Actual Versus Approximation ODE Values'])
  figure
  plot(t,err,'-b.')
  xlabel('Time t')
  ylabel('Y(t)-Y_a(t)')
  title([num2str(nstep),'Steps: Solution Error'])

end