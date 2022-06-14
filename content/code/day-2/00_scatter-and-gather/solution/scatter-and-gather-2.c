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

    int* matrix;
    int i, j;

    if (rank == 0)
    {
        matrix = (int*)(malloc(sizeof(int) * size * size));
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                matrix[i * size + j] = i + j;
            }
        }
    }

    /* Do the scatter */

    int* vector = (int*)(malloc(sizeof(int) * size));

    MPI_Scatter(matrix, size, MPI_INT, vector, size, MPI_INT, 0, comm);

    /* Do the gather */

    int* matrix_2;

    if (rank == 0)
    {
        matrix_2 = (int*)(malloc(sizeof(int) * size * size));
    }

    MPI_Gather(vector, size, MPI_INT, matrix_2, size, MPI_INT, 0, comm);

    /* Check the result */

    int success = 1;
    for (i = 0; i < size; i++)
    {
        if (vector[i] != i + rank)
        {
            success = 0;
        }
    }

    if (rank == 0)
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                if (matrix_2[i * size + j] != i + j)
                {
                    success = 0;
                }
            }
        }
    }

    if (success)
    {
        printf("SUCCESS on rank %d!\n", rank);
    }
    else
    {
        printf("Improvement needed before rank %d can report success!\n", rank);
    }

    /* Clean up and exit */

    if (rank == 0)
    {
        free(matrix);
        free(matrix_2);
    }
    free(vector);

    MPI_Finalize();

    return 0;
}
