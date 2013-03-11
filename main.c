/* Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * Author: Jeroen Mulkers
 * Date: 28/2/2013
 */

#include <stdio.h>
#include <math.h>
#include "mpi.h"

int N=12;

void printfVector(double vec[N]);
void printfMatrix(double matrix[][N], int nrows);
void generateMatrix(double matrix[]);
void matVec(double matrix[], double vector[N], double result[N]);
double norm2(double vector[N]);
double powerMethod(double matrix[], int ntimes);

int main(int argc, char* argv[]) {

  int rank, p;

  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  double matrix[N*N/p];
  generateMatrix(matrix);

  // double lambda = powerMethod(matrix,100);
  // if(rank==0){
  //    printf("%f",lambda);
  // }

  MPI_Finalize();

  return 0;
}

void printfVector(double vec[]){
  for(int i=0; i<N; i++) {
    printf("%1.1f\t",vec[i]);
  }
  printf("\n");
}

void printfMatrix(double matrix[][N], int nrows) {
  for(int i=0; i<nrows; i++) {
    printfVector(matrix[i]);
  }
}

void generateMatrix(double matrix[]){

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  for(int j=0; j<N  ; j++) {
  for(int i=0; i<N/p; i++) {

    if(j-rank*N/p>i) {
      matrix[i+N*j] = 0;
    } else {
      matrix[i+N*j] = rank*(N/p)+i+1;
    }

  }}
}

void matVec(double matrix[], double vector[N], double result[N]){

  MPI_Bcast(vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);


  double temp[N/p];

  for(int i=0; i<N/p; i++){
  for(int j=0; j<N  ; j++){
    temp[i] += matrix[i+N*j] * vector[j];
  }}

  MPI_Gather(temp,N/p,MPI_DOUBLE,result,N/p,MPI_DOUBLE,0,MPI_COMM_WORLD);
}

double norm2(double vector[]){
  double result = 0;
  for(int i=0; i<N;i++){
    result += pow(vector[i],2);
  }
  return pow(result,0.5);
}

double powerMethod(double matrix[], int ntimes) {

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  double vector[N];
  if(rank==0){
    for(int i=0; i<N; i++){
      vector[i]=1;
    }
  }

  for(int n=0; n<ntimes; n++){

    if(rank==0){
      double norm = norm2(vector);
      for(int i=0; i<N; i++){
	vector[i] = vector[i]/norm;
      }
    }

    double temp[N];
    matVec(matrix,vector,temp);
    if(rank==0){
      for(int i=0; i<N; i++){
	vector[i] = temp[i];
      }
    }
  }

  return norm2(vector);
}
