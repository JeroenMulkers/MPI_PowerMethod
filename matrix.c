#include <stdio.h>
#include <assert.h>
#include "mpi.h"
#include "matrix.h"
#include "math.h"

void printfVector(double vec[],int N){
  for(int i=0; i<N; i++) {
    printf("%1.1f\t",vec[i]);
  }
  printf("\n");
}

void printfMatrix(double matrix[], int nrows, int ncolumns) {
  for(int i=0; i<nrows; i++) {
    for(int j=0; j<ncolumns; j++) {
      printf("%1.1f\t",matrix[j+ncolumns*i]);
    }
    printf("\n");
  }
}

void matVec(double matrix[], double vector[], double result[], int N){

  MPI_Bcast(vector, N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  int rank, p;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  double temp[N/p];

  for(int i=0; i<N/p; i++){
  for(int j=0; j<N  ; j++){
    temp[i] += matrix[j+N*i] * vector[j];
  }}

  MPI_Gather(temp,N/p,MPI_DOUBLE,result,N/p,MPI_DOUBLE,0,MPI_COMM_WORLD);
}

double norm2(double vector[], int N){
  double result = 0;
  for(int i=0; i<N;i++){
    result += pow(vector[i],2);
  }
  return pow(result,0.5);
}

double powerMethod(double matrix[], int ntimes, int N) {

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
      double norm = norm2(vector,N);
      for(int i=0; i<N; i++){
	vector[i] = vector[i]/norm;
      }
    }

    double temp[N];
    matVec(matrix,vector,temp,N);
    if(rank==0){
      for(int i=0; i<N; i++){
	vector[i] = temp[i];
      }
    }
  }

  return norm2(vector,N);
}


int norm2_test(){

  int N=17;
  double vector_1[N];
  double vector_2[N];

  for(int i=0; i<N; i++){
    vector_1[i] = 0;
    vector_2[i] = 3.7*(i+1)+1./5.;
  }
  vector_1[7]=1.;

  double norm_1 = norm2(vector_1,N);
  double norm_2 = norm2(vector_2,N);
  int nr = 1000*norm_2;

  int result = 1;
  if ( norm_1 != 1 || nr != 157047 ){
    result = 0;
  }

  return result;
}

void matrix_testAll(){
  assert(norm2_test());
}

