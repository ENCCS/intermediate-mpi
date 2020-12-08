#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  int size, rank, town_size, town_rank;

  // find out the size
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // find out the rank
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  MPI_Comm town;
  MPI_Comm_split(MPI_COMM_WORLD, rank % 2, rank, &town);

  MPI_Comm_size(town, &town_size);
  MPI_Comm_rank(town, &town_rank);

  printf(" rank %d town_rank = %d\n", rank, town_rank);
  printf(" size %d town_size = %d\n", size, town_size);

  MPI_Comm_free(&town);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
