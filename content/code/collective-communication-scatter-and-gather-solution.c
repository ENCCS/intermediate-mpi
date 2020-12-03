#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    /* Initialize the MPI environment and report */
    MPI_Init(&argc, &argv);
    MPI_Comm comm = MPI_COMM_WORLD;
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    /* Prepare the values to scatter */
    float expected_values[4] = { 100, -1000, 3.5, -2.25 };
    float values_to_scatter[4];
    const int rank_of_scatter_root = 0;
    if (rank == rank_of_scatter_root)
    {
        values_to_scatter[0] = expected_values[0];
        values_to_scatter[1] = expected_values[1];
        values_to_scatter[2] = expected_values[2];
        values_to_scatter[3] = expected_values[3];
    }

    /* Report the state before the scatter */
    fprintf(stdout, "On rank %d, pre-scatter values were [%f, %f, %f, %f]\n", rank,
            values_to_scatter[0],
            values_to_scatter[1],
            values_to_scatter[2],
            values_to_scatter[3]);

    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     */
    /* Do the scatter */
    float scattered_value;
    MPI_Scatter(values_to_scatter, 1, MPI_FLOAT,
                &scattered_value, 1, MPI_FLOAT,
                rank_of_scatter_root, comm);

    /* Report the state after the scatter */
    fprintf(stdout, "On rank %d, scattered value was %f\n", rank, scattered_value);

    /* Do some "real work" on the scattered value */
    float result = scattered_value * (rank + 1);
    
    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     */
    /* Gather the result over all ranks to the new root */
    float gathered_values[4];
    const int rank_of_gather_root = 2;
    MPI_Gather(&result, 1, MPI_FLOAT,
               gathered_values, 1, MPI_FLOAT,
               rank_of_gather_root, comm);

    /* Report the state after the gather */
    if (rank == rank_of_gather_root)
    {
        fprintf(stdout, "On rank %d, gathered values were [%f, %f, %f, %f]\n", rank,
                gathered_values[0],
                gathered_values[1],
                gathered_values[2],
                gathered_values[3]);
    }

    /* Report whether the code is correct */
    int success = (result == expected_values[rank] * (rank + 1));

    /* Success on the gather-root rank also means checking the gather */
    if (rank == rank_of_gather_root)
    {
        success = success && ((gathered_values[0] == expected_values[0] * 1) &&
                              (gathered_values[1] == expected_values[1] * 2) &&
                              (gathered_values[2] == expected_values[2] * 3) &&
                              (gathered_values[3] == expected_values[3] * 4));
    }
    if (success)
    {
        fprintf(stdout, "SUCCESS on rank %d!\n", rank);
    }
    else
    {
        fprintf(stdout, "Improvement needed before rank %d can report success!\n", rank);
    }

    /* Clean up and exit */
    MPI_Finalize();
    return 0;
}
