/*
 * Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * File: matrix.h
 * Last modification: 27/3/2013
 *
 * Author: Jeroen Mulkers (student at university of Antwerp)
 * Mail: jeroen.mulkers@student.ua.ac.be
 *
 */


#ifndef MATRIX_H
#define MATRIX_H


void printfVector(double vec[],int N);

void printfMatrix(double matrix[], int nrows, int ncolumns);

void matVec(double matrix[], double vector[], double result[], int N);

double norm2(double vector[], int N);

double powerMethod(double matrix[], int ntimes, int N);

void matrix_testAll();


#endif
