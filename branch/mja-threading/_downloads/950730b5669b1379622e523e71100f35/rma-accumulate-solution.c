#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  MPI_Comm world = MPI_COMM_WORLD;

  // Get my rank
  int rank;
  MPI_Comm_rank(world, &rank);

  // Create the window
  int buffer = 42;
  MPI_Win win;
  MPI_Win_create(&buffer, (MPI_Aint)sizeof(int), sizeof(int), MPI_INFO_NULL,
                 world, &win);

  if (rank == 0) {
    printf("[MPI process 0] Value in my buffer before MPI_Accumulate: "
           "%d.\n",
           buffer);
  }

  // start access epoch
  MPI_Win_fence(0, win);

  if (rank > 0) {
    // Push my value into the first integer in MPI process 0 window
    MPI_Accumulate(&rank, 1, MPI_INT, 0, 0, 1, MPI_INT, MPI_SUM, win);
    printf(
        "[MPI process %d] I accumulate my rank %d in process 0 memory window\n",
        rank, rank);
  }

  // end access epoch
  MPI_Win_fence(0, win);

  if (rank == 0) {
    printf("[MPI process 0] Value in my buffer after MPI_Accumulate: %d.\n",
           buffer);
  }

  // Destroy the window
  MPI_Win_free(&win);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
