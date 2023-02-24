function [x,nit] = conjugateGradient( A,b, x0, maxIt, rtol)
    rk = b-A*x0;
    dk = rk;
    xk = x0;
    RBE = norm(rk)/norm(b);
    k = 0;
    while RBE > rtol
        if k > maxIt
            disp('Max iterations exceeded!')
            return
        end
        %Bulk computations
        Adk = A*dk;
        alphak = (rk.'*rk)/(dk.'*Adk);
        xnext = xk + alphak*dk;
        rnext = rk - alphak*Adk;
        betak = (rnext.'*rnext)/(rk.'*rk);
        dk = rnext + betak*dk;
        % Update residual and guess
        xk = xnext;
        rk = rnext;
        % Data Collection
        RBEnext = norm(b-A*xk)/norm(b);
        ratio = RBEnext/RBE;
        RBE = RBEnext;
        fprintf('CG: k=%3d, delta = %8.2e, ratio=%8.2e\n',k,RBE,ratio);
        k = k + 1;
        nit = k;
    end
    x = xk;
end