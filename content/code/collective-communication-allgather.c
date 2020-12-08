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
    printf("On rank %d, pre-all-gather values were [%d, %d, %d]\n", rank,
            values_to_all_gather[0],
            values_to_all_gather[1],
            values_to_all_gather[2]);

    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     * We want the values_to_all_gather to end up in
     * result_values on all ranks.
     */
    /* Do the all-gather */
    int result_values[12];
    /* MPI_xxx(xxx); */

    /* Report the state after the all-gather */
    printf("On rank %d, all-gathered values were:\n  [", rank);
    for(int i = 0; i < 11; i = i + 1)
    {
        printf("%d, ", result_values[i]);
    }
    printf("%d]\n", result_values[11]);

    /* Report whether the code is correct */
    int success = 1;
    for(int i = 0; i < 12; i = i + 1)
    {
        int expected_value = initial_values[i % 3] * ((i / 3) + 1);
        success = success && (result_values[i] == expected_value);
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
    MPI_Finalize();
    return 0;
}
