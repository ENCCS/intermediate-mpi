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
    printf("MPI process %d sends values:", rank);
    for (int i = 0; i < 4; ++i) {
      printf(" %d", sendbuf[i]);
    }
    printf("\n");
    /* FIXME Non-blocking send of sendbug to rank 1 */
    MPI_Isend( .. );

    /* Here you might do other useful computational work */

    /* FIXME wait on MPI_Isend */
    MPI_Wait( .. );
  } else if (rank == 1) {
    /* FIXME receive data on rank 1 */
    int recvbuf[4];
    MPI_Recv( .. );
    printf("MPI process %d receives values:", rank);
    for (int i = 0; i < 4; ++i) {
      printf(" %d", recvbuf[i]);
    }
    printf("\n");
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
