function [X,Y,out] = nmf_func(M, r, opts)
    [m ,n] = size(M);
    X = rand(m,r);
    Y = rand(r,n);
    maxit = opts.maxit;
    rel_error = norm(X*Y-M, "fro")/norm(M,"fro");
    fprintf('error = %f', rel_error);
    iter = 0;
    maxit = 1;
    while iter < maxit
        iter = iter+1;

        %pre compute 
        XtX = X'*X;
        YtY = Y'*Y;
        
        
        % Lipschitz Constants = spec norm of A'A
        Ly = sqrt(max(eig(XtX)));
        Lx = sqrt(max(eig(YtY)));

        % Update Schemes
        gradX = X*(Y*Y') - M*Y';
        gradY = (X*X')*Y-X'*M + 1;
        X = max(0,X-gradX/Lx);
        Y = max(0,Y-gradY/Ly);
        
        rel_error = norm(X*Y-M, "fro")/norm(M,"fro");
        fprintf('error = %f', rel_error);
        rel_error_his = [rel_error_hi, rel_error];
    end
    out.rel_error = rel_error_his;
end