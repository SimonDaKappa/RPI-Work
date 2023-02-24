function [w,b,out] = ADMM_SVM(X,y,lam,opts)
% ============================================
%   This function is for alternating direction 
%   method of multipliers for solving SVM.
%   Reformulation from paper gives us SVM as
%   min_{S,W_b} 1/2*W_b'*I_hat*W_b + 
%               1/lam * 1-norm(max(0,S))
%       s.t S + MW_b = 1 (col vec)
%
%   Thus f(W_b) = 1/2W_b'*I_hat*W_b, 
%        g(S) = 1norm(max(0,S)),
%        A = I, B = M, C = 1, x = W_b, z = S
%
% ============================================
% input:
%       X: training data, each column is a sample data
%       y: label vector
%       lam: model parameter
%       opts.tol: stopping tolerance
%       opts.maxit: maximum number of outer iteration
%       opts.w0: initial w
%       opts.b0: initial b0
%       opts.beta: penalty parameter
%
% output:
%       w: learned w
%       b: learned b
%       out.hist_pres: historical primal residual
%       out.hist_dres: historical dual residual

% ============================================       

%% Get Size of problem: p is dimension; N is number of data pts
[p, N] = size(X);

%% set parameters
if isfield(opts,'tol')        tol = opts.tol;           else tol = 1e-4;       end
if isfield(opts,'maxit')      maxit = opts.maxit;       else maxit = 500;      end
if isfield(opts,'subtol')     subtol = opts.subtol;     else subtol = 1e-4;    end
if isfield(opts,'maxsubit')   maxsubit = opts.maxsubit; else maxsubit = 5000;  end
if isfield(opts,'w0')         w0 = opts.w0;             else w0 = randn(p,1);  end
if isfield(opts,'b0')         b0 = opts.b0;             else b0 = 0;           end
if isfield(opts,'t0')         t0 = opts.t0;             else t0 = zeros(N,1);  end
if isfield(opts,'beta')       beta = opts.beta;         else beta = 1;         end

%% preloading variables
beta = 0.5;
lam = 0.1;
w = w0;
b = b0;
u = zeros(N,1);

vec_1 = ones(N,1);
X_ones = [X; vec_1'];
I_hat = eye(p+1);
I_hat(end,end) = 0; % used for QP formatting
M = y .* X_ones'; % m for multiple
W_b_term1 = (I_hat + beta*(M')*M) \ (M'); %inv of first term * M'
W_b = [w; b]; % combining weight and bias into 1 variable
S = vec_1 - M*W_b; %simplified hinge-loss input.
S_0 = S;
%% Calculate Primal, Dual Residual

% need two terms of S and W_b in order to calculate
pres = 1e3;
hist_pres = norm(pres);
dres = 1e3;
hist_dres = norm(dres);
    
iter = 0; 
maxit = 1000; %maxit override
%% start of outer loop
while (norm(pres) > tol || norm(dres) > tol) && iter < maxit
    iter = iter + 1;

    % closed form updates
    % W_b
    W_b = W_b_term1 * (beta*(vec_1 - S) - u);

    % S update 
    S_0 = S;
    P = vec_1 - M*W_b - u/2;
    
    % elementwise update formula
    for i = 1:N
        if P(i) < 0 
            S(i) = P(i); 
        elseif P(i) >= 0 && P(i) <= 1/(lam*beta)
            S(i) = 0;
        elseif P(i) > 1/(lam*beta)
            S(i) = P(i) - 1/(lam*beta);
        end
    end

    % primal residual update
    pres = S + M*W_b - vec_1;
    hist_pres = [hist_pres; norm(pres)];
    % dual residual update
    dres = beta*(M')*(S_0 - S);
    hist_dres = [hist_dres; norm(dres)];

    % lagrange multiplier update
    u = u + beta*(pres);
    
    
end


fprintf('out iter = %d, pres = %5.4e, dres = %5.4e\n',iter,norm(pres),norm(dres));

out.hist_pres = hist_pres;
out.hist_dres = hist_dres;
out.iter = iter;

% recover w and b from W_b
w = W_b(1:p);
b = W_b(end);

end



