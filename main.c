/* Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * Author: Jeroen Mulkers
 * Date: 28/2/2013
 */

#include <stdio.h>
#include "mpi.h"

int N=10;

void printfVector(double vec[], int length){
  for(int i=0; i<length; i++) {
    printf("%1.1f\t",vec[i]);
  }
  printf("\n");
}

void printfMatrix(double matrix[][N], int nrows) {
  for(int i=0; i<nrows; i++) {
    printfVector(matrix[i],N);
  }
}

int main(int argc, char* argv[]) {

  int rank;
  int p;

  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  double matrix[2][N];
  if(rank==0){
    for(int j=0; j<N; j++){
      matrix[0][j] = j;
      matrix[1][j] = 2*j;
    }
  }

  if(rank==0){
    printfMatrix(matrix,2);
  }

  MPI_Finalize();

  return 0;
}
