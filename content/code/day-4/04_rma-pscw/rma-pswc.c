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

  MPI_Win win;
  // FIXME create new window and attach it to buf
  MPI_xxx(/*  */);

  // Post/Start/Wait/Complete works with process groups
  // Perform the necessary shenanigans
  // processes with ranks > 0 are origin processes for RMA calls
  // process with rank = 0 is the target process for RMA calls
  MPI_Group comm_group;
  // FIXME get comm_group
  MPI_xxx(/*  */);

  MPI_Group group;
  if (rank == 0) {
    // FIXME Origin group consists of all ranks > 0
    MPI_xxx(/*  */);
    // FIXME initialize the exposure epoch
    MPI_xxx(/*  */);
    // FIXME wait for exposure epoch to finish
    MPI_xxx(/*  */);
  } else {
    // FIXME Target group consists of rank 0
    MPI_xxx(/*  */);
    // FIXME initialize the access epoch
    MPI_xxx(/*  */);
    // FIXME put element at index rank into buffer on rank 0
    MPI_xxx(/*  */);
    // FIXME Terminate the access epoch
    MPI_xxx(/*  */);
  }

  if (rank == 0) {
    printf("on process %d:\n  [", rank);
    for (int i = 0; i < size; ++i) {
      printf(" %f, ", buf[i]);
    }
    printf("]\n");
  }

  // FIXME free window and groups
  MPI_xxx(/*  */);

  MPI_Finalize();

  return 0;
}
