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

  // Create the window
  int window_buffer[4] = {0};
  if (rank == 1) {
      window_buffer[0] = 42;
      window_buffer[1] = 88;
      window_buffer[2] = 12;
      window_buffer[3] = 3;
  }
  MPI_Win win;
  MPI_Win_create(&window_buffer, (MPI_Aint)4 * sizeof(int), sizeof(int),
                 MPI_INFO_NULL, comm, &win);

  // start access epoch
  MPI_Win_fence(0, win);

  int getbuf[4];
  if (rank == 0) {
    // Fetch the value from the MPI process 1 window
    MPI_Get(&getbuf, 4, MPI_INT, 1, 0, 4, MPI_INT, win);
  }

  // end access epoch
  MPI_Win_fence(0, win);

  if (rank == 0) {
    printf("[MPI process 0] Value fetched from MPI process 1 window:");
    for (int i = 0; i < 4; ++i) {
       printf(" %d", getbuf[i]);
    }
    printf("\n");
  }

  // Destroy the window
  MPI_Win_free(&win);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
