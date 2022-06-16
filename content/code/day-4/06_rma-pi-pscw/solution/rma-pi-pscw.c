/* Modified from: https://cvw.cac.cornell.edu/MPIoneSided/piacc_c_solution */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define PI25DT 3.141592653589793238462643

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int rank, size;
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  int n;
  // on rank 0, read the number of points from the input
  if (rank == 0) {
    if (argc < 2) {
      fprintf(stderr, "Usage: %s N\n", argv[0]);
      MPI_Abort(comm, 1);
    }
    sscanf(argv[1], "%d", &n);
    printf("The integration grid has N=%d points\n", n);
    if (n == 0) {
      fprintf(stderr, "N should be greater than 0!\n");
      MPI_Abort(comm, 1);
    }
  }

  // declare/initialize stuff for group shenanigans
  int *ranks = malloc(size);
  for (int i = 0; i < size; ++i) {
    ranks[i] = i;
  }

  MPI_Group comm_group, group;
  MPI_Comm_group(comm, &comm_group);

  double pi = 0.0;

  // create two windows:
  // - one for the number of points, and
  // - one for the computation of pi
  MPI_Win win_n, win_pi;
  MPI_Win_create(&n, sizeof(int), sizeof(int), MPI_INFO_NULL, comm, &win_n);
  MPI_Win_create(&pi, sizeof(double), sizeof(double), MPI_INFO_NULL, comm,
                 &win_pi);

  if (rank == 0) {
    // All ranks except 0 will compute a chunk of the integral.
    // Once they're done, they will accumulate their results on rank 0
    // Hence the *origin group* for RMA consists of ranks 1 to size-1
    MPI_Group_incl(comm_group, size - 1, ranks + 1, &group);
  } else {
    // Target group consists of rank 0, where the accumulation will happen.
    MPI_Group_incl(comm_group, 1, ranks, &group);
  }

  // synchronization *and* RMA for number of points
  if (rank == 0) {
    // initialize exposure epoch for win_n on rank 0 (target rank of RMA)
    MPI_Win_post(group, 0, win_n);
    // finalize exposure epoch
    MPI_Win_wait(win_n);
  } else {
    // initialize access epoch for win_n on rank > 0 (origin ranks of RMA)
    MPI_Win_start(group, 0, win_n);
    // RMA with rank 0 as target process to get value of n
    MPI_Get(&n, 1, MPI_INT, 0, 0, 1, MPI_INT, win_n);
    // finalize acces epoch
    MPI_Win_complete(win_n);
  }

  // compute slice of pi for each process (including on rank 0)
  double h = 1.0 / (double)n;
  double sum = 0.0;

  double x;
  for (int i = rank + 1; i <= n; i += size) {
    x = h * ((double)i - 0.5);
    sum += (4.0 / (1.0 + x * x));
  }
  pi = h * sum;

  // synchronization *and* RMA for final result
  if (rank > 0) {
    // initialize access epoch for win_pi on rank > 0 (origin ranks of RMA)
    MPI_Win_start(group, 0, win_pi);
    // RMA reduction with rank 0 as target process
    MPI_Accumulate(&pi, 1, MPI_DOUBLE, 0, 0, 1, MPI_DOUBLE, MPI_SUM, win_pi);
    // finalize acces epoch
    MPI_Win_complete(win_pi);
  } else {
    // initialiaze exposure epoch for win_pi on rank 0 (target rank of RMA)
    MPI_Win_post(group, 0, win_pi);
    // finalize exposure epoch for win_pi on rank 0 (target rank of RMA)
    MPI_Win_wait(win_pi);
    printf("pi is approximately %.16f, Error is %.16f\n", pi,
           fabs(pi - PI25DT));
  }

  // free windows
  MPI_Win_free(&win_n);
  MPI_Win_free(&win_pi);

  MPI_Finalize();

  return 0;
}
