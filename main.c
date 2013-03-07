/* Applications of parallel computing - mpi
 * Assignment: Implementation of the power method
 * Author: Jeroen Mulkers
 * Date: 28/2/2013
 */

#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[]) {

  int rank;
  int p;

  MPI_Init(&argc, & argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &p);

  MPI_Finalize();

  return 0;
}
