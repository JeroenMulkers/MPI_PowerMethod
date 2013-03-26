function r = norm2(x)
% NORM2 : Euclidean norm of a vector
%
% r = norm2(x); 
% returns the 2-norm of vector x.
% This does the same computation as Matlab's "norm(x)"
%
% John R. Gilbert   11 Jan 2010

n = max(size(x));
r = 0;
for i = 1:n
    r = r + x(i)*x(i);
end;
r = sqrt(r);