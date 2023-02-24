x = [-1.5,1.5];
for i = 1:10
    i
    H = hessian(x);
    G = gradient(x);
    p = -inv(H) * G;
    x = x + p;
    n = norm(G);
    n
end

function y = gradient(x)
    grad1 = -200*x(1)*(x(2)-x(1)^2)^2 + 2*(1-x(1));
    grad2 = 100*(x(2)-x(1)^2);
    y = [grad1;grad2];
end

function y = hessian(x)
    H11 = -200*(x(2)-3*x(1)^2)-2;
    H12 = -200*x(2);
    H22 = 100;
    y = [H11,H12;H12 H22];
end

