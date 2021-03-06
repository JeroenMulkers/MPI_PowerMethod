/*
 * Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * File: matrix_test.c
 * Last modification: 27/3/2013
 *
 * Author: Jeroen Mulkers (student at university of Antwerp)
 * Mail: jeroen.mulkers@student.ua.ac.be
 *
 */


#include <assert.h>
#include <stdio.h>
#include "math.h"
#include "mpi.h"
#include "matrix.h"


static int matVec_test();
static int norm2_test();
static int powerMethod_test();


void matrix_testAll(){

  /* Assert al the test functions */
  assert(norm2_test());
  assert(matVec_test());
  assert(powerMethod_test());

}


static int norm2_test(){

  /* Declaration of two vectors */
  int N=17;
  double vector_1[N];
  double vector_2[N];


  /* Filling of the two vectors */
  for(int i=0; i<N; i++){
    vector_1[i] = 0;
    vector_2[i] = 3.7*(i+1)+1./5.;
  }
  vector_1[7]=1.;


  /* Calculation of the norm of the two vectors */
  double norm_1 = norm2(vector_1,N);
  double norm_2 = norm2(vector_2,N);
  int nr = 1000*norm_2;


  /* Test wheter or not the calculation of the norm is right */
  int result = 1;
  if ( norm_1 != 1 || nr != 157047 )
    result = 0;

  return result;
}



static int matVec_test(){

  int rank, p;
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);


  /* Declaration of a matrix and a vector */
  int N=3*p;
  double matrix[N*N/p];
  double vector[N];


  /* Defention of the matrix and the vector */
  for(int j=0; j<N; j++){
    for(int i=0; i<N/p; i++)
	matrix[j+N*i] = 1;
    vector[j] = 1;
  }


  /* Calculation of the product */
  double result[N];
  matVec(matrix,vector,result,N);


  /* Check wheter or not the result is correct */
  int ok = 1;
  if(rank==0){
    for(int i=0; i<N; i++)
      if(result[i] != N) ok=0;
  }


  /* Broadcast wheter or not the results is correct  */
  MPI_Bcast(&ok, 1, MPI_INT, 0, MPI_COMM_WORLD);

  return ok;
}



static int powerMethod_test(){

  int ok=1;

  int p,rank;
  MPI_Comm_size(MPI_COMM_WORLD, &p);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);


  /* Loop over the 50 different cases */
  for(int n=1; n<=50; n++){


    /* check if the number of processors is suitable for the case */
    if( n%p == 0 ){


      /* Open the file of the case */
      char filename[30];
      sprintf(filename,"./testMatrices/matrix_%d.dat",n);
      FILE *file = fopen(filename,"r");
      if ( file == NULL ){
        printf("couldn't open file %S",filename);
	ok = 0;
      } else {


	/* Read the matrix and the results */
        double matrixBuffer[n*n];
        double lambda_ref;
        float read;
        for(int i=0; i<n*n; i++){
          fscanf(file,"%f",&read);
          matrixBuffer[i] = (double) read;
        }
        fscanf(file,"%f",&read);
        lambda_ref = (double) read;


	/* Spread the matrix over the different processors */
	double matrix[n*n/p];
	for(int i=0; i<n*n/p; i++){
      	  matrix[i] = matrixBuffer[i+rank*n*n/p];
      	}


	/* Use the powermethod for calculating the largest EV */
	double lambda = powerMethod(matrix,1000,n);


	/* Check wheter or not the results is correct */
	if(rank==0){
	  // printf("n=%d\n",n);
	  // printf("labda_ref %f\n",lambda_ref);
	  // printf("lambda    %f\n",lambda);
	  // printf("diff      %f\n",fabs(lambda-lambda_ref));
      	  if(fabs(lambda-lambda_ref) > 0.0001)
      	    ok = 0;
      	}


	/* Broadcast wheter or not the result is correct */
      	MPI_Bcast(&ok, 1, MPI_INT, 0, MPI_COMM_WORLD);

      }

      /* Close the file */
      fclose(file);

    }
  }

  return ok;
}
