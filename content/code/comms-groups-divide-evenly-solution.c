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
  // list of process ranks in first and second groups
  int ranks1[2] = {0, 1};
  int ranks2[2] = {2, 3};

  MPI_Group world_group;
  MPI_Group new_group;
  MPI_Comm new_comm;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // check that the size of MPI_COMM_WORLD matches with our grouping expecations
  // NOTE it is bad practice to do this!
  if (size != NPROCS) {
    fprintf(stderr, "Error: Must have %d processes in MPI_COMM_WORLD\n",
            NPROCS);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  // I will be sending my rank as message
  sendbuf = rank;
  count = 1;

  // get the group of MPI_COMM_WORLD
  MPI_Comm_group(MPI_COMM_WORLD, &world_group);

  // split the processes in half, one half goes to ranks1 the other to ranks2
  if (rank < NPROCS / 2) {
    MPI_Group_incl(world_group, NPROCS / 2, ranks1, &new_group);
  } else {
    MPI_Group_incl(world_group, NPROCS / 2, ranks2, &new_group);
  }

  MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_comm);

  // compute total of ranks in MPI_COMM_WORLD in the newer, smaller communicator
  MPI_Allreduce(&sendbuf, &recvbuf, count, MPI_INT, MPI_SUM, new_comm);

  // rank in the new group
  MPI_Group_rank(new_group, &new_rank);

  printf("rank= %d newrank= %d recvbuf= %d\n", rank, new_rank, recvbuf);

  MPI_Group_free(&world_group);
  MPI_Group_free(&new_group);
  MPI_Comm_free(&new_comm);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
