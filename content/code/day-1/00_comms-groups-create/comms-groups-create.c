#include <stdio.h>

#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
 
    /* size and rank from global communicator */
 
    int global_size, global_rank;
 
    MPI_Comm_size(MPI_COMM_WORLD, &global_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &global_rank);
 
    printf("global rank %d in MPI_COMM_WORLD of size %d\n", global_rank, global_size);
 
    /* global group */
 
    MPI_Group global_group;
    MPI_Comm_group(MPI_COMM_WORLD, &global_group);
 
    /* FIXME: create a local group by excluding some ranks */
 
    int excl_ranks[ ... ];
    excl_ranks[0] = ...
    ...
 
    MPI_Group local_group;
    MPI_Group_excl( ... );
 
    /* FIXME: create a local communicator from local group */
 
    MPI_Comm local_comm;
    MPI_Comm_create( ... );
 
    if (local_comm != MPI_COMM_NULL)
    {
        /* FIXME: get size and rank from the local communicator */
 
        int local_size, local_rank;
 
        MPI_Comm_size( ... );
        MPI_Comm_rank( ... );
 
        printf( ... );
 
        /* FIXME: complete MPI_Comm_free (why does one need to call it inside the if block?) */
 
        MPI_Comm_free( ... );
    }
 
    /* FIXME: complete MPI_Group)free */
 
    MPI_Group_free( ... );
    MPI_Group_free( ... );
 
    MPI_Finalize();

    return 0;
}
