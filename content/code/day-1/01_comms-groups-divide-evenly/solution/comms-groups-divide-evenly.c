/* Adapated from:
 * https://github.com/UoB-HPC/hpc-course-examples/blob/master/mpi/advanced/example10/group_to_comm.c
 */

#include <mpi.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    // rank and size from global communicator

    int global_rank, global_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
 
    // global group

    MPI_Group global_group;
    MPI_Comm_group(MPI_COMM_WORLD, &global_group);

    // incl_ranks

    int num_incl_ranks_1 = global_size / 2;
    int num_incl_ranks_2 = global_size - num_incl_ranks_1;

    int* incl_ranks_1 = (int*)(malloc(sizeof(int) * num_incl_ranks_1));
    int* incl_ranks_2 = (int*)(malloc(sizeof(int) * num_incl_ranks_2));

    int i;
    for (i = 0; i < num_incl_ranks_1; i++)
    {
        incl_ranks_1[i] = i;
    }
    for (i = 0; i < num_incl_ranks_2; i++)
    {
        incl_ranks_2[i] = num_incl_ranks_1 + i;
    }

    // local group

    MPI_Group local_group;
    if (global_rank < num_incl_ranks_1)
    {
        MPI_Group_incl(global_group, num_incl_ranks_1, incl_ranks_1, &local_group);
    }
    else
    {
        MPI_Group_incl(global_group, num_incl_ranks_2, incl_ranks_2, &local_group);
    }

    // local communicator
 
    MPI_Comm local_comm;
    MPI_Comm_create(MPI_COMM_WORLD, local_group, &local_comm);

    // rank in local communicator
 
    int local_rank;
    MPI_Comm_rank(local_comm, &local_rank);
 
    // send global rank as message

    int sendbuf = global_rank;
    int recvbuf;
    int count = 1;
 
    // compute sum of global ranks in local communicator
 
    MPI_Allreduce(&sendbuf, &recvbuf, count, MPI_INT, MPI_SUM, local_comm);
 
    printf("global_rank= %d local_rank= %d recvbuf= %d\n", global_rank, local_rank, recvbuf);

    free(incl_ranks_1);
    free(incl_ranks_2);
 
    MPI_Comm_free(&local_comm);
    MPI_Group_free(&local_group);
    MPI_Group_free(&global_group);
 
    MPI_Finalize();
 
    return 0;
}
