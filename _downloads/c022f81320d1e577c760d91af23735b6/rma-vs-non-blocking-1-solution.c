#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  // Get the number of processes and check only 2 processes are used
  int size;
  MPI_Comm_size(comm, &size);
  if (size != 2) {
    printf("This application is meant to be run with 2 processes.\n");
    MPI_Abort(comm, EXIT_FAILURE);
  }
  int rank;
  MPI_Comm_rank(comm, &rank);

  // Get my rank and do the corresponding job
  if (rank == 0) {
    int sendbuf[4] = {42, 88, 12, 3};
    MPI_Request request;
    printf("MPI process %d sends values:", rank);
    for (int i = 0; i < 4; ++i) {
      printf(" %d", sendbuf[i]);
    }
    printf("\n");
    MPI_Isend(&sendbuf, 4, MPI_INT, 1, 0, comm, &request);

    /* Here you might do other useful computational work */

    // Let's wait for the MPI_Isend to complete before progressing further.
    MPI_Wait(&request, MPI_STATUS_IGNORE);
  } else if (rank == 1) {
    int recvbuf[4];
    MPI_Recv(&recvbuf, 4, MPI_INT, 0, 0, comm, MPI_STATUS_IGNORE);
    printf("MPI process %d receives values:", rank);
    for (int i = 0; i < 4; ++i) {
      printf(" %d", recvbuf[i]);
    }
    printf("\n");
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
