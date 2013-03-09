/* Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * Author: Jeroen Mulkers
 * Date: 28/2/2013
 */

#include <stdio.h>
#include <math.h>
#include "mpi.h"

int N=12;

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

void generateMatrix(double matrix[][N]){

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  for(int i=0; i<N/p; i++) {
  for(int j=0; j<N  ; j++) {

    if(j-rank*N/p>i) {
      matrix[i][j] = 0;
    } else {
      matrix[i][j] = rank*(N/p)+i+1;
    }

  }}
}

void matVec(double matrix[][N], double vector[N], double result[N]){

  MPI_Bcast(vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);


  double temp[N/p];

  for(int i=0; i<N/p; i++){
  for(int j=0; j<N  ; j++){
    temp[i] += matrix[i][j] * vector[j];
  }}

  MPI_Gather(temp,N/p,MPI_DOUBLE,result,N/p,MPI_DOUBLE,0,MPI_COMM_WORLD);
}

double norm2(double vector[], int size){
  double result = 0;
  for(int i=0; i<size;i++){
    result += pow(vector[i],2);
  }
  return pow(result,0.5);;
}


int main(int argc, char* argv[]) {

  int rank, p;

  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  double matrix[N/p][N];
  generateMatrix(matrix);

  double vector[N];
  if(rank==0){
    for(int i=0; i<N; i++){
      vector[i] = i;
    }
  }

  if(rank==0){
    printfVector(vector,N);
    printf("%f",norm2(vector,N));
  }

  MPI_Finalize();

  return 0;
}
