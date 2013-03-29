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
#include <stdlib.h>
#include <assert.h>
#include "mpi.h"
#include "matrix.h"


void generateMatrix(double matrix[], int N);


int main(int argc, char* argv[]) {

  /* Set parameters */
  int N = atoi(argv[1]);
  int nIterations = atoi(argv[2]);


  /* Start parallel calculations */
  int rank, p;
  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);


  /* p has to be a divisor of N !! */
  if(rank==0) assert(!(N%p));


  /* Test the used algorithms */
  //matrix_testAll();


  /* Generate the matrix */
  double matrix[N*N/p];
  generateMatrix(matrix,N);


  /* Run the powerMethod algorithm */
  double start = MPI_Wtime();
  double lambda = powerMethod(matrix,nIterations,N);
  double stop = MPI_Wtime();



  /* Calculating times */
  double timediff = stop - start;
  double times[p];
  double average = 0;
  MPI_Gather(&timediff,1,MPI_DOUBLE,times,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
  if(rank==0){
    for(int i=0; i<p; i++)
      average += times[i];
    average /= p;
  }


  /* Print the results */
  if(rank==0)
    printf("dimension\t%d\tlambda\t%f\ttime\t%f\n",N,lambda,average);


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
