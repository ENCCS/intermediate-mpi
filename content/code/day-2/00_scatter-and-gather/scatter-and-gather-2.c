#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

int main(int argc, char *argv[])
{
    /* Initialize the MPI environment and report */

    MPI_Init(&argc, &argv);

    MPI_Comm comm = MPI_COMM_WORLD;

    int rank, size;
    MPI_Comm_rank( ... );
    MPI_Comm_size( ... );

    /* Prepare the matrix and vector */

    int* matrix;
    int i, j;

    if (rank == 0)
    {
        matrix = (int*)(malloc(sizeof(int) * size * size));

        /* FIXME: assign values for elements in matrix */
        ...
    }

    /* Do the scatter */

    int* vector = (int*)(malloc(sizeof(int) * size));

    /* FIXME: complete MPI_Scatter */
    MPI_Scatter( ... );

    /* Do the gather */

    int* matrix_2;

    if (rank == 0)
    {
        matrix_2 = (int*)(malloc(sizeof(int) * size * size));
    }

    /* FIXME: complete MPI_Gather */
    MPI_Gather( ... );

    /* Check the result */

    int success = 1;
    for (i = 0; i < size; i++)
    {
        /* FIXME: check the values in vector */
        if (vector[i] != ...)
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
                /* FIXME: check the values in matrix_2 */
                if (matrix_2[i * size + j] != ...)
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

    /* FIXME: complete the code for cleaning up */
    if (rank == 0)
    {
        free( ... );
        free( ... );
    }
    free( ... );

    MPI_...();

    return 0;
}
