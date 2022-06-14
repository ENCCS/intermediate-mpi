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
 
    // FIXME: create local communicator using MPI_Comm_split
 
    int color = ...;
    int key = global_rank;

    MPI_Comm local_comm;
    MPI_Comm_split( ... );

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

    // FIXME: complete MPI_Comm_free
 
    MPI_Comm_free( ... );
 
    MPI_Finalize();
 
    return 0;
}
