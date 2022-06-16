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
  MPI_Win_create(buf, size * sizeof(double), sizeof(double), MPI_INFO_NULL,
                 comm, &win);

  // origin processes
  if (rank > 0) {
    // Request lock of process 0
    MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, win);
    // put element at index rank into buffer on rank 0
    MPI_Put(buf, 1, MPI_DOUBLE, 0, rank, 1, MPI_DOUBLE, win);
    // Block until put succeeds
    MPI_Win_unlock(0, win);
  }

  // there is no synchronization on the target process!!!

  if (rank == 0) {
    printf("on process %d:\n  [", rank);
    for (int i = 0; i < size; ++i) {
      printf(" %f, ", buf[i]);
    }
    printf("]\n");
  }

  // Free the window
  MPI_Win_free(&win);

  MPI_Finalize();

  return 0;
}
