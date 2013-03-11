/* Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * Author: Jeroen Mulkers
 * Date: 28/2/2013
 */

#include <stdio.h>
#include "mpi.h"
#include "matrix.h"

void generateMatrix(double matrix[], int N);

int main(int argc, char* argv[]) {

  int N=12;

  int rank, p;

  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  matrix_testAll();

  double matrix[N*N/p];
  generateMatrix(matrix,N);
  printfMatrix(matrix,N/p,N);

  double lambda = powerMethod(matrix,100,N);
  if(rank==0){
     printf("%f",lambda);
  }

  MPI_Finalize();

  return 0;
}

void generateMatrix(double matrix[], int N){

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  for(int j=0; j<N  ; j++) {
  for(int i=0; i<N/p; i++) {

    if(j-rank*N/p>i) {
      matrix[j+N*i] = 0;
    } else {
      matrix[j+N*i] = rank*(N/p)+i+1;
    }

  }}
}
