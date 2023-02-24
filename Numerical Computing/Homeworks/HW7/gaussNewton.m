function xc = gaussNewton( r,rx, x0,tol,maxIt )
  n = length(x0);
  xc = x0;
  res = Inf;
  k= 0;
  while res > tol
    if k > maxIt
      disp('Max Iterations Exceeded!'); return
    end
    A = rx(xc);
    vk = (A.'*A)\(-A.'*r(xc));
    xnext = xc - vk;
    res = norm(xnext-xc);
    xc = xnext;
    fprintf('GaussNewton: k=%4d: x=[%13.6e',k,xc(1));
    for j=2:n fprintf(',%13.6e',xc(j)); end
    fprintf('] || correction ||_2=%8.2e\n',norm(vk));
    k = k+1;
  end
end