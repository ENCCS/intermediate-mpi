#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int size;
  MPI_Comm_size(comm, &size);
  if (size != 2) {
    printf(
        "This application is meant to be run with 2 MPI processes, not %d.\n",
        size);
    MPI_Abort(comm, EXIT_FAILURE);
  }

  // Get my rank
  int rank;
  MPI_Comm_rank(comm, &rank);

  /* FIXME create the memory window */
  int *window_buffer;
  MPI_Win win;
  MPI_Win_allocate( .. );

  // start access epoch
  MPI_Win_fence(0, win);

  // local store
  if (rank == 1) {
    window_buffer[0] = -1;
    window_buffer[1] = -1;
    window_buffer[2] = -1;
    window_buffer[3] = -1;
  }

  // start access epoch
  MPI_Win_fence(0, win);

  if (rank == 0) {
    int putbuf[4] = {42, 88, 12, 3};
    /* FIXME Put the value into the MPI process 1 window */
    MPI_Put( .. );
  }

  // end access epoch
  MPI_Win_fence(0, win);

  if (rank == 1) {
    printf("[MPI process 1] Value put by MPI process 0:");
    for (int i = 0; i < 4; ++i) {
      printf(" %d", window_buffer[i]);
    }
    printf("\n");
  }

  // Destroy the window
  MPI_Win_free(&win);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
