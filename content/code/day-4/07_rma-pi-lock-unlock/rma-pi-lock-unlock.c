/* Modified from: https://cvw.cac.cornell.edu/MPIoneSided/pilul_c_solution */

#include <math.h>
#include <stdio.h>

#include <mpi.h>

#define PI25DT 3.141592653589793238462643

int main(int argc, char *argv[]) {

  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int size;
  MPI_Comm_size(comm, &size);
  int rank;
  MPI_Comm_rank(comm, &rank);

  int n;
  // on rank 0, read the number of points from the input
  if (rank == 0) {
    if (argc < 2) {
      fprintf(stderr, "Usage: %s N\n", argv[0]);
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    sscanf(argv[1], "%d", &n);
    printf("The integration grid has N=%d points\n", n);
    if (n == 0) {
      fprintf(stderr, "N should be greater than 0!\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
  }

  double pi = 0.0;

  // FIXME create two windows:
  // - one for the number of points, and
  // - one for the computation of pi
  MPI_Win win_n, win_pi;
  MPI_xxx(/*  */);

  // every rank > 0 originates a MPI_Get to obtain n
  // (or rank = 0 could originate a MPI_Put)
  if (rank > 0) {
    // FIXME lock the window on rank 0 (target process)
    MPI_xxx(/*  */);
    // FIXME RMA with rank 0 as target process
    MPI_xxx(/*  */);
    // FIXME unlock the window on rank 0 (target process)
    MPI_xxx(/*  */);
  }

  // compute slice of pi for each process (including on rank 0)
  double h = 1.0 / (double)n;
  double sum = 0.0;

  double x;
  for (int i = rank + 1; i <= n; i += size) {
    x = h * ((double)i - 0.5);
    sum += (4.0 / (1.0 + x * x));
  }
  // result of computation on this rank
  double my_pi = h * sum;

  if (rank > 0) {
    // FIXME lock the window on rank 0 (target process)
    MPI_xxx(/*  */);
    // FIXME RMA with rank 0 as target process
    MPI_xxx(/*  */);
    // FIXME unlock the window on rank 0 (target process)
    MPI_xxx(/*  */);
  }

  // FIXME barrier to make sure that rank 0 is done with its chunk of the computation
  MPI_xxx(/*  */);

  if (rank == 0) {
    // sum up my_pi on rank 0 with the result of the reduction with
    // MPI_Accumulate
    pi += my_pi;
    printf("pi is approximately %.16f, Error is %.16f\n", pi,
           fabs(pi - PI25DT));
  }

  // FIXME free the windows
  MPI_xxx(/*  */);

  MPI_Finalize();

  return 0;
}
