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

    /* Prepare the matrix and vector */

    const int n_rows = 1559;
    const int n_cols = 179;
    int i, j;

    double* matrix;
    double* vector = (double*)(malloc(sizeof(double) * n_cols));

    if (rank == 0)
    {
        matrix = (double*)(malloc(sizeof(double) * n_rows * n_cols));

        for (i = 0; i < n_rows; i++)
        {
            for (j = 0; j < n_cols; j++)
            {
                /* FIXME: assign values for elements in matrix */
                matrix[i * n_cols + j] = ...;
            }
        }

        for (j = 0; j < n_cols; j++)
        {
            /* FIXME: assign values for elements in vector */
            vector[j] = ...;
        }
    }

    /* Do the scatterv */

    int* counts = (int*)(malloc(sizeof(int) * size));
    int* displs = (int*)(malloc(sizeof(int) * size));

    int ave = n_rows / size;
    int rem = n_rows % size;

    for (i = 0; i < size; i++)
    {
        if (i < rem)
        {
            /* FIXME: determine counts */
            counts[i] = ...;
        }
        else
        {
            /* FIXME: determine counts */
            counts[i] = ...;
        }

        if (i == 0)
        {
            displs[i] = 0;
        }
        else
        {
            displs[i] = displs[i-1] + counts[i-1];
        }
    }

    double* row_vectors = (double*)(malloc(sizeof(double) * counts[rank]));

    /* FIXME: complete MPI_Scatterv */
    MPI_Scatterv( ... );

    /* Do the bcast */

    MPI_Bcast(vector, n_cols, MPI_DOUBLE, 0, comm);

    /* Do matrix vector multiplication */

    double* local_product = (double*)(malloc(sizeof(double) * (counts[rank] / n_cols)));

    for (i = 0; i < counts[rank] / n_cols; i++)
    {
        double p = 0.0;

        for (j = 0; j < n_cols; j++)
        {
            p += row_vectors[i * n_cols + j] * vector[j];
        }

        local_product[i] = p;
    }

    /* Do the gatherv */

    double* final_product;

    if (rank == 0)
    {
        final_product = (double*)(malloc(sizeof(double) * n_rows));
    }

    int* count_rows = (int*)(malloc(sizeof(int) * size));
    int* displ_rows = (int*)(malloc(sizeof(int) * size));

    for (i = 0; i < size; i++)
    {
        count_rows[i] = counts[i] / n_cols;
        displ_rows[i] = displs[i] / n_cols;
    }

    /* FIXME: complete MPI_Gatherv */
    MPI_Gatherv( ... );

    /* Check the result */

    if (rank == 0)
    {
        int success = 1;

        for (i = 0; i < n_rows; i++)
        {
            double p = 0.0;

            for (j = 0; j < n_cols; j++)
            {
                p += matrix[i * n_cols + j] * vector[j];
            }

            if (p != final_product[i])
            {
                success = 0;
            }
        }

        if (success)
        {
            printf("SUCCESS!\n");
        }
        else
        {
            printf("Improvement needed!\n");
        }
    }

    /* Clean up and exit */

    if (rank == 0)
    {
        free(final_product);
        free(matrix);
    }
    free(displ_rows);
    free(count_rows);
    free(displs);
    free(counts);
    free(local_product);
    free(row_vectors);
    free(vector);

    MPI_Finalize();

    return 0;
}
