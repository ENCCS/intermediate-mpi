#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  MPI_Aint lb, extent;
  int size;

  // char
  printf("sizeof(char) = %ld\n", sizeof(char));
  MPI_Type_get_extent(MPI_CHAR, &lb, &extent);
  MPI_Type_size(MPI_CHAR, &size);
  printf("For MPI_CHAR:\n  lowerbound = %ld; extent = %ld; size = %d\n", lb,
         extent, size);

  // int
  printf("sizeof(int) = %ld\n", sizeof(int));
  MPI_Type_get_extent(MPI_INT, &lb, &extent);
  MPI_Type_size(MPI_INT, &size);
  printf("For MPI_INT:\n  lowerbound = %ld; extent = %ld; size = %d\n", lb,
         extent, size);

  // float
  printf("sizeof(float) = %ld\n", sizeof(float));
  MPI_Type_get_extent(MPI_FLOAT, &lb, &extent);
  MPI_Type_size(MPI_FLOAT, &size);
  printf("For MPI_FLOAT:\n  lowerbound = %ld; extent = %ld; size = %d\n", lb,
         extent, size);

  // double
  printf("sizeof(double) = %ld\n", sizeof(double));
  MPI_Type_get_extent(MPI_DOUBLE, &lb, &extent);
  MPI_Type_size(MPI_DOUBLE, &size);
  printf("For MPI_DOUBLE:\n  lowerbound = %ld; extent = %ld; size = %d\n", lb,
         extent, size);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
