#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work! Start
     * an MPI environment suitable for OpenMP fork-join parallelism.
     */

    /* Initialize the MPI environment and report */
    int required, provided;
    required = MPI_THREAD_FUNNELED;
    MPI_Init_thread(NULL, NULL, required, &provided);
    /* MPI_xxx(xxx); */
        
    printf("Initialization required %d and %d was provided\n", required, provided);

    /* Clean up and exit */
    MPI_Finalize();
    return 0;
}
