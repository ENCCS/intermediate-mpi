#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  MPI_Comm world = MPI_COMM_WORLD;

  // Get my rank
  int rank;
  MPI_Comm_rank(world, &rank);

  /* FIXME create window object */
  int buffer = 42;
  MPI_Win win;
  MPI_Win_create( .. );

  if (rank == 0) {
    printf("[MPI process 0] Value in my buffer before MPI_Accumulate: "
           "%d.\n",
           buffer);
  }

  // start access epoch
  MPI_Win_fence(0, win);

  if (rank > 0) {
    /* FIXME accumulate this process' rank into the memory window of the root process by summing */
    MPI_Accumulate( .. );
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
