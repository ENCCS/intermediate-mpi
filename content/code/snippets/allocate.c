#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  // allocate window
  double *buf;
  MPI_Win win;
  MPI_Win_allocate((MPI_Aint)(10 * sizeof(double)), sizeof(double),
                   MPI_INFO_NULL, MPI_COMM_WORLD, &buf, &win);

  // do something with win

  // free window and the associated memory
  MPI_Win_free(&win);

  MPI_Finalize();
}
