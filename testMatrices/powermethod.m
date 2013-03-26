function lambda = powermethod(A)
% POWERMETHOD : Power method to estimate norm of dominant eigenvalue
%
% lambda = powermethod(A);
%
% This routine generates a random vector, then repeatedly 
% multiplies matrix A by the vector and normalizes the result
% to have length 1.  The norm converges to the magnitude of
% the dominant eigenvalue, which is returned as lambda.
%
% This is a sequential Matlab template -- CS140 homework 2 is
% to implement this in parallel.
%
% John R. Gilbert    13 Jan 2006 / modified 11 Jan 2010

[n,n] = size(A);       % number of rows and columns in A
x = ones(n,1);         % creates a starting n-vector of all ones
for i = 1:1000         
    x = x / norm2(x);  % norm2(x) is sqrt(x(1)^2 + x(2)^2 + ... + x(n)^2)
    x = A * x;         % use your parallel matrix * vector routine here
end;
lambda = norm2(x);