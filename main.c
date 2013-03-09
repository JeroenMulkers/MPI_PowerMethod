/* Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * Author: Jeroen Mulkers
 * Date: 28/2/2013
 */

#include <stdio.h>
#include "mpi.h"

void printfVector(double vec[], int length){
  for(int i=0; i<length; i++) {
    printf("%1.1f\t",vec[i]);
  }
  printf("\n");
}

int main(int argc, char* argv[]) {

  int rank;
  int p;

  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  int N = 10;
  double vector[N];
  if(rank==0){
    for(int i=0; i<N; i++){
      vector[i]=i;
    }
  }

  if(rank==0){
    printfVector(vector,N);
  }



  MPI_Finalize();

  return 0;
}
