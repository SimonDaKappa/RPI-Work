function [w,b,out] = ALM_SVM(X,y,lam,opts)
%=============================================
%
% augmented Lagrangian method for solving SVM
% min_{w,b,t} sum(t) + lam/2*norm(w)^2
% s.t. y(i)*(w'*X(:,i)+b) >= 1-t(i)
%      t(i) >= 0, i = 1,...,N
%
%===============================================
%
% ==============================================
% input:
%       X: training data, each column is a sample data
%       y: label vector
%       lam: model parameter
%       opts.tol: stopping tolerance
%       opts.maxit: maximum number of outer iteration
%       opts.subtol: stopping tolerance for inner-loop
%       opts.maxsubit: maxinum number of iteration for inner-loop
%       opts.w0: initial w
%       opts.b0: initial b0
%       opts.t0: initial t0
%       opts.beta: penalty parameter
%
% output:
%       w: learned w
%       b: learned b
%       out.hist_pres: historical primal residual
%       out.hist_dres: historical dual residual
%       out.hist_subit: historical iteration number of inner-loop

% ======================================================

%% get size of problem: p is dimension; N is number of data pts
[p,N] = size(X);

%% set parameters
if isfield(opts,'tol')        tol = opts.tol;           else tol = 1e-4;       end
if isfield(opts,'maxit')      maxit = opts.maxit;       else maxit = 500;      end
if isfield(opts,'subtol')     subtol = opts.subtol;     else subtol = 1e-4;    end
if isfield(opts,'maxsubit')   maxsubit = opts.maxsubit; else maxsubit = 5000;  end
if isfield(opts,'w0')         w0 = opts.w0;             else w0 = randn(p,1);  end
if isfield(opts,'b0')         b0 = opts.b0;             else b0 = 0;           end
if isfield(opts,'t0')         t0 = opts.t0;             else t0 = zeros(N,1);  end
if isfield(opts,'beta')       beta = opts.beta;         else beta = 1;         end


alpha0 = 0.5;
alpha = 0.5;
inc_ratio = 2;
dec_ratio = 0.6;

w = w0; b = b0; t = max(0,t0);
% initialize dual variable
u = zeros(N,1);

%% compute the primal residual and save to pres

pres = ;

% save historical primal residual
hist_pres = pres;

%% compute dual residual

dres = ;
hist_dres = dres;

hist_subit = 0;

iter = 0; subit = 0;
%% start of outer loop
while max(pres,dres) > tol & iter < maxit
    iter = iter + 1;
    % call the subroutine to update primal variable (w,b,t)
    w0 = w;
    b0 = b;
    t0 = t;
    
    % fill in the subsolver by yourself
    % if slack variables are introduced, you will have more variables
    [w,b,t] = subsolver(w0,b0,t0,subtol,maxsubit);
    
    hist_subit = [hist_subit; subit];
    
    % update multiplier u
    
    u = ;
    
    % compute primal residual and save to hist_pres

    pres = ;
    hist_pres = [hist_pres; pres];
    
    % compute gradient of ordinary Lagrangian function about (w,b,t)
    grad_w = ;
    grad_b = ;
    grad_t = ;
    
    % compute the dual residual and save to hist_dres
    dres = ;
    hist_dres = [hist_dres; dres];
    
    fprintf('out iter = %d, pres = %5.4e, dres = %5.4e, subit = %d\n',iter,pres,dres,subit);
end

out.hist_pres = hist_pres;
out.hist_dres = hist_dres;
out.hist_subit = hist_subit;

%% =====================================================
% subsolver for primal subproblem
    function [w,b,t] = subsolver(w0,b0,t0,subtol,maxsubit)
        % fill this subsolver
    end
%=====================================================

end



