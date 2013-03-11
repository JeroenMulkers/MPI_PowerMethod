#ifndef MATRIX_H
#define MATRIX_H

void printfVector(double vec[],int N);

void printfMatrix(double matrix[], int nrows, int ncolumns);

void matVec(double matrix[], double vector[], double result[], int N);

double norm2(double vector[], int N);

double powerMethod(double matrix[], int ntimes, int N);

void matrix_testAll();

#endif
