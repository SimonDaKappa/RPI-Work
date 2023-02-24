f = @(t,X) [X(2);-4*X(1)+cos(3*t)];
soln = @(t) (cos(2*t)-cos(3*t))/5;

for k = 0:4
  nstep = 50*2^k;
  [t,y] = RK4(f,0,10,[0;0],nstep);
  y_exact = soln(t);
  y_approx = y(1,:);
  err(k+1) = max(y_exact-y_approx);
  fprintf(' k=%d nstep=%4d h=%9.3e err=%9.3e ',k,nstep,(10-0)/nstep,err(k+1));
  if k>0  
    fprintf(' ratio=%4.2f rate=%4.2f\n',err(k)/err(k+1),log2(err(k)/err(k+1)));
  else 
    fprintf('\n'); 
  end
  figure
  plot(t,y_exact,'-bo',t,y_approx,'-g.')
  legend('Actual Y','RK4')
  xlabel('Time t')
  ylabel('Y(t)')
  title([num2str(nstep),' Steps: Actual Versus RK4'])
  figure
  plot(t,y_exact-y_approx,'-b.')
  xlabel('Time t')
  ylabel('Y(t)-Ya(t)')
  title([num2str(nstep),' Steps: Solution Error'])
end