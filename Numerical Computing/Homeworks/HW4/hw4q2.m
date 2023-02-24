A = [2,1,1,0;4,3,3,1;8,7,9,5;6,7,9,8]
[L,U] = luFactorNoPivoting(A);
L
U
check = L*U

b = [7;23;69;70];
x = luSolveNoPivoting(b,L,U);
x
if A*x == b
    disp("solution correct!")
end