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


void generateMatrix(double matrix[], int N);


int main(int argc, char* argv[]) {

  /* Set parameters */
  int N=100;
  int nIterations=1000;


  /* Start parallel calculations */
  int rank, p;
  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);


  /* Test the used algorithms */
  //matrix_testAll();


  /* Generate the matrix */
  double matrix[N*N/p];
  generateMatrix(matrix,N);


  /* Run the powerMethod algorithm */
  double start = MPI_Wtime();
  double lambda = powerMethod(matrix,nIterations,N);
  double stop = MPI_Wtime();


  /* Print the results */
  if(rank==0) printf("lambda = %f\n",lambda);
  printf("pr%d: %f\n",rank,stop-start);


  /* End MPI */
  MPI_Finalize();

  return 0;
}



void generateMatrix(double matrix[], int N){

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  /* Define the matrix on the (different) processors */
  for(int j=0; j<N  ; j++) {
  for(int i=0; i<N/p; i++) {

    if(j-rank*N/p>i)
      matrix[j+N*i] = 0;
    else
      matrix[j+N*i] = rank*(N/p)+i+1;

  }}

}
