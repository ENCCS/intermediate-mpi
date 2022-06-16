/* Modified from: https://cvw.cac.cornell.edu/MPIoneSided/lul_c_solution */

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

  double *buf = (double *)(malloc(sizeof(double) * size));
  for (int i = 0; i < size; i++) {
    buf[i] = rank * 11; // Give each rank unique data
  }

  MPI_Win win;
  // FIXME create a window and attach it to buf
  MPI_xxx(/*  */);

  // origin processes
  if (rank > 0) {
    // FIXME Request lock of process 0
    MPI_xxx(/*  */);
    // FIXME put element at index rank into buffer on rank 0
    MPI_xxx(/*  */);
    // FIXME Block until put succeeds
    MPI_xxx(/*  */);
  }

  // there is no synchronization on the target process!!!

  if (rank == 0) {
    printf("on process %d:\n  [", rank);
    for (int i = 0; i < size; ++i) {
      printf(" %f, ", buf[i]);
    }
    printf("]\n");
  }

  // FIXME Free the window
  MPI_xxx(/*  */);

  MPI_Finalize();

  return 0;
}
