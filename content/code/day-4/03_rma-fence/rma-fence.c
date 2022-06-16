/* Modified from: https://cvw.cac.cornell.edu/MPIoneSided/fence_c_solution */

#include <stdio.h>

#include <mpi.h>

#define BUFSZ 10

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int rank;
  MPI_Comm_rank(comm, &rank);

  // initialize buffer to 0
  int buf[BUFSZ] = {0};

  // only on rank 0 the elements of buf are different from zero
  if (rank == 0) {
    for (int i = 0; i < BUFSZ; ++i) {
      buf[i] = (i + 1) * 3;
    }
  }

  MPI_Win win;
  // FIXME create a window and attach it to buf
  MPI_xxx(/*  */);

  printf("Before Get on %d:\n  [", rank);
  for (int i = 0; i < BUFSZ; ++i) {
    printf(" %d, ", buf[i]);
  }
  printf("]\n");

  // initialize access epoch
  // assert that there were no local RMA operations prior to this epoch
  // FIXME
  MPI_xxx(/*  */);

  // ranks > 0 originate MPI_Get with rank 0 as target
  // FIXME
  if (/*  */) {
    // FIXME
    MPI_xxx(/*  */);
  }

  // finalize the access epoch
  // this blocks until the MPI_Get is complete
  // assert that there will be no further local RMA operations
  // FIXME
  MPI_xxx(/*  */);

  printf("After Get on %d:\n  [", rank);
  for (int i = 0; i < BUFSZ; ++i) {
    printf(" %d, ", buf[i]);
  }
  printf("]\n");

  // Free up our window
  // FIXME
  MPI_xxx(/*  */);

  MPI_Finalize();

  return 0;
}
