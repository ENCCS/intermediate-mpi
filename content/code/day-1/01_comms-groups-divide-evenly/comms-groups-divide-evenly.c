/* Adapated from:
 * https://github.com/UoB-HPC/hpc-course-examples/blob/master/mpi/advanced/example10/group_to_comm.c
 */

#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    // get rank and size from global communicator

    int global_rank, global_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
 
    // FIXME: create global group

    MPI_Group global_group;
    MPI_Comm_group( ... );

    // FIXME: create and initialize incl_ranks_1 and incl_ranks_2

    int num_incl_ranks_1 = ...
    int num_incl_ranks_2 = ...

    int* incl_ranks_1 = (int*)(malloc(sizeof(int) * num_incl_ranks_1));
    int* incl_ranks_2 = (int*)(malloc(sizeof(int) * num_incl_ranks_2));

    int i;
    for (i = 0; i < num_incl_ranks_1; i++)
    {
        incl_ranks_1[i] = ...
    }
    for (i = 0; i < num_incl_ranks_2; i++)
    {
        incl_ranks_2[i] = ...
    }

    // FIXME: create local group using MPI_Group_incl

    MPI_Group local_group;
    if (global_rank < num_incl_ranks_1)
    {
        MPI_Group_incl( ... );
    }
    else
    {
        MPI_Group_incl( ... );
    }

    // FIXME: create local communicator
 
    MPI_Comm local_comm;
    MPI_Comm_create( ... );

    // FIXME: get rank in local communicator
 
    int local_rank;
    MPI_Comm_rank( ... );
 
    // send global rank as message

    int sendbuf = global_rank;
    int recvbuf;
    int count = 1;
 
    // compute sum of global ranks in local communicator
 
    MPI_Allreduce(&sendbuf, &recvbuf, count, MPI_INT, MPI_SUM, local_comm);
 
    printf("global_rank= %d local_rank= %d recvbuf= %d\n", global_rank, local_rank, recvbuf);

    free(incl_ranks_1);
    free(incl_ranks_2);

    // FIXME: complete MPI_Comm_free and MPI_Group_free
 
    MPI_Comm_free( ... );
    MPI_Group_free( ... );
    MPI_Group_free( ... );
 
    MPI_Finalize();
 
    return 0;
}
