A1 = [1 2; 2 2];
A2 = [4 8 1;0 2 -2;3 6 7];
[Q1,R1] = mgs(A1)
fprintf('||A-QR||_2 = %1.14e, ||QTQ-I||_2 = %1.14e\n',norm(A1-Q1*R1),norm(Q1.'*Q1-eye(2)))
[Q2,R2] = mgs(A2)
fprintf('||A-QR||_2 = %1.14e, ||QTQ-I||_2 = %1.14e\n',norm(A2-Q2*R2),norm(Q2.'*Q2-eye(3)))
