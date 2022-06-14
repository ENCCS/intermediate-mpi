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
            vector_a[i] = (double)(i);
            vector_b[i] = (double)(n_elements - i);
        }
    }

    /* Do the scatter */

    int n_local_elements = n_elements / size;

    double* local_vector_a = (double*)(malloc(sizeof(double) * n_local_elements));
    double* local_vector_b = (double*)(malloc(sizeof(double) * n_local_elements));

    MPI_Scatter(vector_a, n_local_elements, MPI_DOUBLE, local_vector_a, n_local_elements, MPI_DOUBLE, 0, comm);
    MPI_Scatter(vector_b, n_local_elements, MPI_DOUBLE, local_vector_b, n_local_elements, MPI_DOUBLE, 0, comm);

    /* Do local computation */

    struct timespec ts;

    timespec_get(&ts, TIME_UTC);
    double t0 = (double)(ts.tv_sec) + (double)(ts.tv_nsec) * 1e-9;

    double local_product = 0.0;

    for (i = 0; i < n_local_elements; i++)
    {
        local_product += local_vector_a[i] * local_vector_b[i];
    }

    if (rank == 0)
    {
        for (i = n_local_elements * size; i < n_elements; i++)
        {
            local_product += vector_a[i] * vector_b[i];
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

    MPI_Gather(&dt, 1, MPI_DOUBLE, elapsed_time, 1, MPI_DOUBLE, 0, comm);

    /* Do the reduce */

    double final_product;

    MPI_Reduce(&local_product, &final_product, 1, MPI_DOUBLE, MPI_SUM, 0, comm);

    if (rank == 0)
    {
        double ref_product = 0.0;
        for (i = 0; i < n_elements; i++)
        {
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
            dt_sum += elapsed_time[i];
            if (elapsed_time[i] > max_dt)
            {
                max_dt = elapsed_time[i];
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
