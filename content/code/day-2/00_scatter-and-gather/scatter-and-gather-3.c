#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[])
{
    /* Initialize the MPI environment and report */

    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;

    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    /* Prepare the data */

    const int n_elements = 111323;

    double* vector_a;
    double* vector_b;
    int i;

    if (rank == 0)
    {
        vector_a = (double*)(malloc(sizeof(double) * n_elements));
        vector_b = (double*)(malloc(sizeof(double) * n_elements));

        for (i = 0; i < n_elements; i++)
        {
            /* FIXME: assign values for elements in vector_a and vector_b */
            vector_a[i] = ... ;
            vector_b[i] = ... ;
        }
    }

    /* Do the scatter */

    int n_local_elements = n_elements / size;

    /* FIXME: complete malloc for local vectors */
    double* local_vector_a = (double*)(malloc( ... ));
    double* local_vector_b = (double*)(malloc( ... ));

    /* FIXME: complete MPI_Scatter */
    MPI_Scatter( ... );
    MPI_Scatter( ... );

    /* Do local computation and record timing */

    struct timespec ts;

    timespec_get(&ts, TIME_UTC);
    double t0 = (double)(ts.tv_sec) + (double)(ts.tv_nsec) * 1e-9;

    double local_product = 0.0;

    for (i = 0; i < n_local_elements; i++)
    {
        /* FIXME: complete calculation of local product */
        local_product += ... ;
    }

    if (rank == 0)
    {
        for (i = n_local_elements * size; i < n_elements; i++)
        {
            /* FIXME: take care of remaining elements on rank 0, 
             *        in case number of elements is not divisible
             *        by number of processes */
            local_product += ... ;
        }
    }

    timespec_get(&ts, TIME_UTC);
    double t1 = (double)(ts.tv_sec) + (double)(ts.tv_nsec) * 1e-9;

    /* Do the gather */

    double dt = t1 - t0;
    double* elapsed_time;

    if (rank == 0)
    {
        elapsed_time = (double*)(malloc(sizeof(double) * size));
    }

    /* FIXME: complete MPI_Gather of elapsed time */
    MPI_Gather( ... );

    /* Do the reduce */

    double final_product;

    /* FIXME: complete MPI_Reduce of product */
    MPI_Reduce( ... );

    if (rank == 0)
    {
        double ref_product = 0.0;
        for (i = 0; i < n_elements; i++)
        {
            /* FIXME: complete calculation of reference */
            ref_product += vector_a[i] * vector_b[i];
        }

        double diff = fabs(ref_product - final_product);
        printf("diff = %.6e\n", diff);

        if (diff < 1.0e-8)
        {
            printf("SUCCESS!\n");
        }
        else
        {
            printf("Improvement needed!\n");
        }

        double dt_sum = 0.0;
        double max_dt = 0.0;
        for (i = 0; i < size; i++)
        {
            /* FIXME: calculate sum of dt and find maximum value of dt */
            dt_sum += ... ;
            if ( ... )
            {
                max_dt = ... ;
            }
        }

        double load_imb = 1.0 - (dt_sum / size) / max_dt;
        printf("Time spent in computation: %.1f microseconds\n", max_dt * 1e+6);
        printf("Load imbalance of computation: %.1f%%\n", load_imb * 100.0);
    }

    /* Clean up and exit */

    if (rank == 0)
    {
        free(vector_a);
        free(vector_b);
        free(elapsed_time);
    }
    free(local_vector_a);
    free(local_vector_b);

    MPI_Finalize();

    return 0;
}
