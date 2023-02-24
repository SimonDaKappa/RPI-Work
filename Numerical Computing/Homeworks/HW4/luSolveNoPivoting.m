function x = luSolveNoPivoting(b,L,U)
    % Lc = b
    % Forward Substitution 
    sz = size(L);
    n = sz(1);
    c=zeros(n,1);
    for j=1:n
        c(j)=b(j)/L(j,j);
        b(j+1:n)=b(j+1:n)-L(j+1:n,j)*c(j);
    end
    % Ux = c
    % Backward Substitution
    x=zeros(n,1);
    for j=n:-1:1
        x(j)=c(j)/U(j,j);
        c(1:j-1)=c(1:j-1)-U(1:j-1,j)*x(j);
    end


end