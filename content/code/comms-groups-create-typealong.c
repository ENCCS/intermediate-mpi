#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  int size, rank;

  // find out the size
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  // find out the rank
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  printf(" rank %d in MPI_COMM_WORLD of size %d\n", rank, size);

  MPI_Group world_group;
  MPI_Comm_group(MPI_COMM_WORLD, &world_group);

  MPI_Group most_popular;
  int ranks[1];
  ranks[0] = 1;
  MPI_Group_excl(world_group, 1, ranks, &most_popular);

  MPI_Comm town;
  MPI_Comm_create(MPI_COMM_WORLD, most_popular, &town);
  MPI_Group_free(&most_popular);
  //MPI_Comm_free(&town);
  MPI_Group_free(&world_group);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
