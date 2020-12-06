#include <stdio.h>

#include <mpi.h>

struct Pair {
  int first;
  char second;
};

int main(int argc, char *argv[]) {
  // designated initilization
  struct Pair my_pair = {.first = 5, .second = 'G'};

  // initialize MPI
  MPI_Init(&argc, &argv);

  // build up the typemap for Pair
  // the type signature for Pair
  MPI_Datatype typesig[2] = {MPI_INT, MPI_CHAR};
  // how many of each type in a "block" of Pair
  int block_lengths[2] = {1, 1};
  // displacements of data members in Pair
  MPI_Aint displacements[2];
  // why not use pointer arithmetic directly?
  MPI_Get_address(&my_pair.first, &displacements[0]);
  MPI_Get_address(&my_pair.second, &displacements[1]);

  // create and commit the new type
  MPI_Datatype mpi_pair;
  MPI_Type_create_struct(2, block_lengths, displacements, typesig, &mpi_pair);
  MPI_Type_commit(&mpi_pair);

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

  // Pair
  printf("sizeof(my_pair) = %ld\n", sizeof(my_pair));
  MPI_Type_get_extent(mpi_pair, &lb, &extent);
  MPI_Type_size(mpi_pair, &size);
  printf("For mpi_pair:\n  lowerbound = %ld; extent = %ld; size = %d\n", lb,
         extent, size);

  MPI_Type_free(&mpi_pair);

  MPI_Finalize();

  return 0;
}
