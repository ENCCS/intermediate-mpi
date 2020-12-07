#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    /* Initialize the MPI environment and report */
    int required, provided;
    required = MPI_THREAD_FUNNELED;
    MPI_Init_thread(NULL, NULL, required, &provided);
        
    fprintf(stdout, "Initialization required %d and %d was provided\n", required, provided);

    MPI_Query_thread(&provided);
    fprintf(stdout, "The thread query reported that level %d was provided\n", provided);

    int is_master;
    MPI_Is_thread_main(&is_master);
    fprintf(stdout, "Is this the main thread on rank %d? %s\n", is_master ? "yes" : "no");

    /* Clean up and exit */
    MPI_Finalize();
    return 0;
}
