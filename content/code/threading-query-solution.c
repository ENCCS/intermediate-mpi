#include <omp.h>
#include "mpi.h"
#include <stdio.h>

/* Help pretty-print some strings for the MPI_THREAD_* constants */
const char* mpi_thread_strings[4] = { "MPI_THEAD_SINGLE",
                                       "MPI_THREAD_FUNNELED",
                                       "MPI_THREAD_SERIALIZED",
                                       "MPI_THREAD_MULTIPLE" };

void report_whether_thread_is_master(int thread_id, int num_threads, int rank)
{
    int is_master;
    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     * Call the function that asks the MPI library to report whether
     * the calling thread is the master thread.
     */
    MPI_Is_thread_main(&is_master);
    printf("Is this thread with id %d of %d the main thread on rank %d? %s\n",
           thread_id, num_threads, rank, is_master ? "yes" : "no");
}

int main(int argc, char **argv)
{
    /* Initialize the MPI environment and report */
    int required, provided;
    required = MPI_THREAD_FUNNELED;
    MPI_Init_thread(NULL, NULL, required, &provided);
    MPI_Comm comm = MPI_COMM_WORLD;
    int rank;
    MPI_Comm_rank(comm, &rank);

    printf("Initialization required %s, and reported that %s was provided\n",
           mpi_thread_strings[required],
           mpi_thread_strings[provided]);

    /* If the program can't run, stop running */
    if (required != provided)
    {
        printf("Sorry, the MPI library does not provide "
               "this threading level! Aborting!\n");
        MPI_Abort(comm, 1);
    }

    /* ==== CHALLENGE ====
     *
     * Uncomment and fix the MPI call to make this code work!
     * Call the function that asks the MPI library to report the level
     * of threading support available.
     */
    /* This query should return the same value as for MPI_Init_thread, and
     * is useful in cases where that return value is not available. */
    int provided_query;
    MPI_Query_thread(&provided_query);
    printf("The query about threading support reported that level %s was provided\n",
           mpi_thread_strings[provided_query]);

    /* Also valuable in such cases is information on whether this is
     * the main thread, so that MPI can be used in MPI_THREAD_FUNNELED
     * case. */
    report_whether_thread_is_master(omp_get_thread_num(), omp_get_num_threads(), rank);

#pragma omp parallel
    {
        /* Let's see that the other threads are *not* master threads */
        report_whether_thread_is_master(omp_get_thread_num(), omp_get_num_threads(), rank);
        /* Only the master thread enters this block */
        #pragma omp master
        {
            report_whether_thread_is_master(omp_get_thread_num(), omp_get_num_threads(), rank);
        }
    }

    /* Clean up and exit */
    MPI_Finalize();
    return 0;
}
