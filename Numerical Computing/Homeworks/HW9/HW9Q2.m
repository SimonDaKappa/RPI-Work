f = @(t,X) [X(2);-4*X(1)+cos(3*t)];
soln = @(t) (cos(2*t)-cos(3*t))/5;
for k = 0:4
  nstep = 50*2^k;
  [t,y,maxerr] = explicitTrapezoid(soln,f,0,10,[0;0],nstep);
  err(k+1) = maxerr;
  fprintf(' k=%d nstep=%4d h=%9.3e err=%9.3e ',k,nstep,(10-0)/nstep,err(k+1));
  if k>0  
    fprintf(' ratio=%4.2f rate=%4.2f\n',err(k)/err(k+1),log2(err(k)/err(k+1)));
  else 
    fprintf('\n'); 
  end
end