#include <stdio.h>

#include <mpi.h>

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);
 
    int world_size, world_rank;
 
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
 
    printf("global rank %d in MPI_COMM_WORLD of size %d\n", world_rank, world_size);
 
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
 
    int excl_ranks[2];
    excl_ranks[0] = 0;
    excl_ranks[1] = 1;
 
    MPI_Group local_group;
    MPI_Group_excl(world_group, 2, excl_ranks, &local_group);
 
    MPI_Comm local_comm;
    MPI_Comm_create(MPI_COMM_WORLD, local_group, &local_comm);
 
    if (local_comm != MPI_COMM_NULL)
    {
        int local_size, local_rank;
 
        MPI_Comm_size(local_comm, &local_size);
        MPI_Comm_rank(local_comm, &local_rank);
 
        printf("global rank %d, local rank %d in local_comm of size %d\n", world_rank, local_rank, local_size);
 
        MPI_Comm_free(&local_comm);
    }
 
    MPI_Group_free(&local_group);
    MPI_Group_free(&world_group);
 
    MPI_Finalize();
 
    return 0;
}
