%
% Solve Ax=b using the Preconditioned Conjugate Gradient algorithm
%
% M (input) : preconditioner, a symmetric positive definite matrix
% A (input) : a symmetric positive definite matrix
% b (input) : right-hand-side
% x0 (input) : initial guess
% maxIt (input) : maximum number of iterations
% rtol (input) : relative backward error convergence tolerance
% x (output) : approximate solution
% nit (output) : number of iterations used
% rbe (output) : array holding the relative backward error at each step
%
function [x,nit,rbe] = preconditionedConjugateGradient( M, A,b, x0, maxIt, rtol, verbose )
    xk = x0;
    rk = b-A*x0;
    zk = M\rk;
    dk = rk;
    rbe = [norm(rk)/norm(b)];
    k=0;
    while rbe(k+1) > rtol
        if k > maxIt, disp('Max Iterations Exceeded'); x = xk; nit = k; return; end
        Adk = A*dk;
        alpha = ((rk.')*zk)/((dk.')*Adk);
        xnext = xk + alpha*dk;
        rnext = rk - alpha*Adk;
        znext = M\rnext;
        beta = ((rnext.')*znext)/((rk.')*zk);
        dnext = znext + beta*dk;
        % Update Variables for next iteration
        xk = xnext;
        rk = rnext;
        zk = znext;
        dk = dnext;
        % Data Formatting
        rbe = [rbe, norm(b-A*xk)/norm(b)];
        fprintf('PCG: k=%3d, delta = %8.2e, ratio=%8.2e\n',k,rbe(k+2),rbe(k+2)/rbe(k+1));
        % Testing
        if verbose == 2
            xk
        end
        if verbose == 1
            fprintf('PCF Final Value, x = [%8.2e', xk(1));
            for j = 1:size(xk)
            fprintf(', %8.2e', xk(j))
            end
        fprintf(']\n')
        end
        k = k + 1;
    end
    nit = k;
    x = xk;
end