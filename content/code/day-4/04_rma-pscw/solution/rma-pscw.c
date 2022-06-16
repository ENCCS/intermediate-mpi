/* Modified from: https://cvw.cac.cornell.edu/MPIoneSided/pscw_c_solution */

#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int size;
  MPI_Comm_size(comm, &size);

  int rank;
  MPI_Comm_rank(comm, &rank);

  // creat a buffer of size equal to the size of the communicator
  double *buf = (double *)(malloc(sizeof(double) * size));
  // save ranks of each process, used later on to create groups
  int *ranks = (int *)(malloc(sizeof(int) * size));
  for (int i = 0; i < size; ++i) {
    buf[i] = rank * 11;
    ranks[i] = i;
  }

  if (rank == 0) {
    printf("on process %d:\n  [", rank);
    for (int i = 0; i < size; ++i) {
      printf(" %f, ", buf[i]);
    }
    printf("]\n");
  }

  // create new window and attach it to buf
  MPI_Win win;
  MPI_Win_create(buf, sizeof(double) * size, sizeof(double), MPI_INFO_NULL,
                 comm, &win);

  // Post/Start/Wait/Complete works with process groups
  // Perform the necessary shenanigans
  // processes with ranks > 0 are origin processes for RMA calls
  // process with rank = 0 is the target process for RMA calls
  MPI_Group comm_group;
  MPI_Comm_group(comm, &comm_group);

  MPI_Group group;
  if (rank == 0) {
    // Origin group consists of all ranks > 0
    MPI_Group_incl(comm_group, size - 1, ranks + 1, &group);
    // initialize the exposure epoch
    MPI_Win_post(group, 0, win);
    // wait for exposure epoch to finish
    MPI_Win_wait(win);
  } else {
    // Target group consists of rank 0
    MPI_Group_incl(comm_group, 1, &ranks[0], &group);
    // initialize the access epoch
    MPI_Win_start(group, 0, win);
    // put element at index rank into buffer on rank 0
    MPI_Put(buf, 1, MPI_DOUBLE, 0, rank, 1, MPI_DOUBLE, win);
    // Terminate the access epoch
    MPI_Win_complete(win);
  }

  if (rank == 0) {
    printf("on process %d:\n  [", rank);
    for (int i = 0; i < size; ++i) {
      printf(" %f, ", buf[i]);
    }
    printf("]\n");
  }

  // free window and groups
  MPI_Win_free(&win);
  MPI_Group_free(&group);
  MPI_Group_free(&comm_group);

  MPI_Finalize();

  return 0;
}
