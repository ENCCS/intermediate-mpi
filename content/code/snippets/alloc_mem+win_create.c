#include <mpi.h>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  // allocate memory
  double *buf;
  MPI_Alloc_mem((MPI_Aint)(10 * sizeof(double)), MPI_INFO_NULL, &buf);

  // create window
  MPI_Win win;
  MPI_Win_create(buf, (MPI_Aint)(10 * sizeof(double)), sizeof(double),
                 MPI_INFO_NULL, MPI_COMM_WORLD, &win);

  // do something with win

  // free window
  MPI_Win_free(&win);

  // free memory
  MPI_Free_mem(buf);

  MPI_Finalize();
}
