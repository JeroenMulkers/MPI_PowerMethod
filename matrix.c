/*
 * Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * File: matrix.c
 * Last modification: 27/3/2013
 *
 * Author: Jeroen Mulkers (student at university of Antwerp)
 * Mail: jeroen.mulkers@student.ua.ac.be
 *
 */


#include <stdio.h>
#include "mpi.h"
#include "matrix.h"
#include "math.h"


double norm2(double vector[], int N){

  /* Add the square of each element */
  double result = 0;
  for(int i=0; i<N;i++)
    result += pow(vector[i],2);

  /* The norm of the vector is the square root of the sum */
  return pow(result,0.5);
}



void matVec(double matrix[], double vector[], double result[], int N){

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);


  /* Broadcast the vector defined on pr0 */
  MPI_Bcast(vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);


  /* Set temporary result to zero */
  double temp[N/p];
  for(int i=0; i<N/p; i++)
    temp[i]=0;


  /* Perform the actual matrix multiplication in parallel */
  for(int i=0; i<N/p; i++)
  for(int j=0; j<N  ; j++)
    temp[i] += matrix[j+N*i] * vector[j];


  /* Gather the results from the different processors */
  MPI_Gather(temp,N/p,MPI_DOUBLE,result,N/p,MPI_DOUBLE,0,MPI_COMM_WORLD);

}



double powerMethod(double matrix[], int ntimes, int N) {

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);


  /* Define starting vector */
  double vector[N];
  if(rank==0){
    for(int i=0; i<N; i++)
      vector[i]=1;
  }


  /* The actual iteration process */
  for(int n=0; n<ntimes; n++){


    /* Normalize the vector*/
    if(rank==0){
      double norm = norm2(vector,N);
      for(int i=0; i<N; i++)
	vector[i] = vector[i]/norm;
    }


    /* Calculate the product of the matrix and the vector */
    double temp[N];
    matVec(matrix,vector,temp,N);
    if(rank==0){
      for(int i=0; i<N; i++)
	vector[i] = temp[i];
    }

  }

  /* The result is the norm of the vector */
  return norm2(vector,N);
}



void printfVector(double vec[],int N){

  /* Print each element seperated with a tab */
  for(int i=0; i<N; i++)
    printf("%1.1f\t",vec[i]);

  /* End with a new line */
  printf("\n");

}



void printfMatrix(double matrix[], int nrows, int ncolumns) {

  /* Iterate over the rows in the matrix */
  for(int i=0; i<nrows; i++){

    /* Print each element af a row seperated with a tab */
    for(int j=0; j<ncolumns; j++){
      printf("%1.1f\t",matrix[j+ncolumns*i]);
    }

    /* At the end of each row, start a new line */
    printf("\n");

  }
}
