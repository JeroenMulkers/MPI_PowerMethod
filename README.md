MPI_PowerMethod
===============

The power method uses matrix-vector multiplication to estimate the size of the largest eigenvalue of a matrix A. An attempt is made to implement this algorithm in parallel.

Comments
--------

Matrices are put in single arrays. This is useful for passing the matrices to functions. The disadvantage is that the code becomes a little harder to read.
