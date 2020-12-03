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

    /* Prepare the values to all-gather */
    int initial_values[3] = { 100, -1000, 3 };
    int values_to_all_gather[3];
    values_to_all_gather[0] = initial_values[0] * (rank + 1);
    values_to_all_gather[1] = initial_values[1] * (rank + 1);
    values_to_all_gather[2] = initial_values[2] * (rank + 1);

    /* Report the state before the all-gather */
    fprintf(stdout, "On rank %d, pre-all-gather values were [%d, %d, %d]\n", rank,
            values_to_all_gather[0],
            values_to_all_gather[1],
            values_to_all_gather[2]);

    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     */
    /* Do the all-gather */
    int all_gathered_values[12];
    MPI_Allgather(values_to_all_gather, 3, MPI_INT,
                  &all_gathered_values, 3, MPI_INT,
                  comm);

    /* Report the state after the all-gather */
    fprintf(stdout, "On rank %d, all-gathered values were:\n  [", rank);
    for(int i = 0; i < 11; i = i + 1)
    {
        fprintf(stdout, "%d, ", all_gathered_values[i]);
    }
    fprintf(stdout, "%d]\n", all_gathered_values[11]);

    /* Report whether the code is correct */
    int success = 1;
    for(int i = 0; i < 12; i = i + 1)
    {
        int expected_value = initial_values[i % 3] * ((i / 3) + 1);
        success = success && (all_gathered_values[i] == expected_value);
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
