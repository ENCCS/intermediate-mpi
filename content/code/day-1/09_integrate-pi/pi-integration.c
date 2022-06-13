#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define PI 3.141592653589793238462643

int main(int argc, char *argv[]) {

    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
 
    int size, rank;
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);

    long int num_points;
 
    if (rank == 0) {
        if (argc < 2) {
            fprintf(stderr, "Usage: %s number_of_points \n", argv[0]);
            MPI_Abort(comm, 1);
        }
        sscanf(argv[1], "%ld", &num_points);
    }
 
    // FIXME: broadcast num_points (note that it is long int)
    MPI_Bcast( ... );

    double delta_x = 1.0 / (double)(num_points);

    long int local_num_points = num_points / size;
    if (num_points % size != 0) {
        local_num_points += 1;
    }

    // FIXME: determine the start and end on each rank
    long int start = ...
    long int end = ...
    ...

    printf("rank %d: start=%ld, end=%ld\n", rank, start, end);

    // FIXME: compute local contribution to integration
    //        \int_{0}^{1} [ 4.0 / (1.0 + x^2) ] dx
    double local_pi = 0.0;
    long int i;
    for (i = start; i < end; i++) {
        ...
    }
    ...

    // FIXME: compute pi using MPI_Reduce
    double global_pi;
    MPI_Reduce( ... );

    if (rank == 0) {
        printf("pi = %22.12f (error: %.3e)\n", global_pi, fabs(global_pi - PI));
    }

    MPI_Finalize();
 
    return 0;
}
