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

    /* Prepare the values to all-to-all */
    int initial_values[3] = { 100, -1000, 3 };
    int values_to_all_to_all[12];
    for(int i = 0; i < 12; i = i + 1)
    {
        values_to_all_to_all[i] = initial_values[i % 3] * (rank + 1) + ((i / 3) + 1);
    }

    /* Report the state before the all-to-all */
    fprintf(stdout, "On rank %d, values before the all-to-all were:\n  [", rank);
    for(int i = 0; i < 11; i = i + 1)
    {
        fprintf(stdout, "%d, ", values_to_all_to_all[i]);
    }
    fprintf(stdout, "%d]\n", values_to_all_to_all[11]);

    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     */
    /* Do the all-to-all */
    int result_values[12];
    MPI_Alltoall(values_to_all_to_all, 3, MPI_INT,
                 &result_values, 3, MPI_INT,
                 comm);

    /* Report the state after the all-to-all */
    fprintf(stdout, "On rank %d, values after the all-to-all were:\n  [", rank);
    for(int i = 0; i < 11; i = i + 1)
    {
        fprintf(stdout, "%d, ", result_values[i]);
    }
    fprintf(stdout, "%d]\n", result_values[11]);

    /* Report whether the code is correct */
    int success = 1;
    for(int i = 0; i < 12; i = i + 1)
    {
        int expected_value = initial_values[i % 3] * ((i / 3) + 1) + (rank + 1);
        success = success && (result_values[i] == expected_value);
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
