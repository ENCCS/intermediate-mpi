/* Adapated from:
 * https://github.com/UoB-HPC/hpc-course-examples/blob/master/mpi/advanced/example10/group_to_comm.c
 */

#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define NPROCS 4

int main(int argc, char *argv[]) {
  int rank;
  int size;
  int new_rank;
  int sendbuf;
  int recvbuf;
  int count;

  /* FIXME define lists of processed in first and second group */
  int ranks1[2] = ..;
  int ranks2[2] = ..;

  /* FIXME define group and communicator variables */
  MPI_Group ..;
  MPI_Comm ..;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  /* FIXME check that the size of MPI_COMM_WORLD matches with NPROCS
   * NOTE it is bad practice to do this, but it's fine for the sake of an exercise!
   */
  if (size != NPROCS) {
      ..
  }

  // I will be sending my rank as message
  sendbuf = rank;
  count = 1;

  /* FIXME get the group of MPI_COMM_WORLD */
  // get the group of MPI_COMM_WORLD
  MPI_Comm_group(.., ..);

  /* FIXME  split the processes in half, one half goes to ranks1 the other to ranks2
   * call MPI_Group_incl to do this
   */

  /* FIXME create new communicator */
  MPI_Comm_create(.., .., ..);

  // compute total of ranks in MPI_COMM_WORLD in the newer, smaller communicator
  // we will discuss collective operations later on in the lesson!
  MPI_Allreduce(&sendbuf, &recvbuf, count, MPI_INT, MPI_SUM, new_comm);

  /* FIXME get rank in the new group */
  MPI_Group_rank(.., ..);

  printf("rank= %d newrank= %d recvbuf= %d\n", rank, new_rank, recvbuf);

  /* FIXME clean up groups and communicators */

  MPI_Finalize();

  return EXIT_SUCCESS;
}
