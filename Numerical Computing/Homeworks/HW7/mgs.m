function [Q,R] = mgs( A )
% Modified Gram-Schmidt :
% Compute the reduced QR factorization : A = Q R
% A (input) : m x n matrix
% Q (output) : m x n matrix with orthonormal columns
% R (output) : n x n matrix, upper triangular
[m,n] = size(A);
Q = zeros(m,n); R = zeros(n,n);
for j = 1:n
  y=A(:,j);
  for i = 1:j-1
    R(i,j)=Q(:,i).'*y;
    y=y-R(i,j)*Q(:,i);
  end
  R(j,j)=norm(y);
  Q(:,j)=y/R(j,j);
end