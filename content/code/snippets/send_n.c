#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#define SIZE 5

int main(int argc, char *argv[]) {
  int rank;
  int size;

  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  if (size != 2) {
    if (rank == 0) {
      fprintf(stdout, "Only two ranks is supported for this exercise, "
                      "please re-run with two ranks\n");
    }
    MPI_Finalize();
    return EXIT_FAILURE;
  }

  int buffer[SIZE];
  memset(buffer, 42, SIZE * sizeof(int));

  MPI_Status status;

  if (rank == 0) {
    fprintf(stdout, "rank %d send\n", rank);
    for (int i = 0; i < SIZE; ++i) {
      fprintf(stdout, "buffer[%d] = %d\n", i, buffer[i]);
    }
    MPI_Send(buffer, SIZE, MPI_INT, 1, 0, comm);
  } else {
    MPI_Recv(buffer, SIZE, MPI_INT, 0, 0, comm, &status);
    fprintf(stdout, "rank %d recv\n", rank);
    for (int i = 0; i < SIZE; ++i) {
      fprintf(stdout, "buffer[%d] = %d\n", i, buffer[i]);
    }
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
