#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define PI 3.141592653589793238462643

int main(int argc, char *argv[]) {

    /* ==== CHALLENGE ====
     *
     * Uncomment the line and fix the MPI call to make this code work!
     * We want to use fork-join parallelism, so pick a more suitable
     * threading mode for OpenMP parallel regions */
    /* Initialize the MPI environment and check */
    int provided, required = MPI_THREAD_FUNNELED;
    MPI_Init_thread(NULL, NULL, required, &provided);
    MPI_Comm comm = MPI_COMM_WORLD;
 
    /* If the program can't run, stop running */
    if (required != provided)
    {
        printf("Sorry, the MPI library does not provide "
               "this threading level! Aborting!\n");
        MPI_Abort(comm, 1);
    }

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
 
    MPI_Bcast(&num_points, 1, MPI_LONG_INT, 0, comm);

    double delta_x = 1.0 / (double)(num_points);

    long int local_num_points = num_points / size;
    if (num_points % size != 0) {
        local_num_points += 1;
    }

    long int start = local_num_points * rank;
    long int end = local_num_points * (rank + 1);
    if (end > num_points) {
        end = num_points;
    }

    printf("rank %d: start=%ld, end=%ld\n", rank, start, end);

    double local_pi = 0.0;
    long int i;
#pragma omp parallel for reduction(+:local_pi)
    for (i = start; i < end; i++) {
        double x = delta_x * ((double)(i) + 0.5);
        local_pi += 1.0 / (1.0 + x * x);
    }
    local_pi *= 4.0 * delta_x;

    double global_pi;
    MPI_Reduce(&local_pi, &global_pi, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

    if (rank == 0) {
        printf("pi = %22.12f (error: %.3e)\n", global_pi, fabs(global_pi - PI));
    }

    MPI_Finalize();
 
    return 0;
}
