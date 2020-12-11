#include "mpi.h"
#include <stdio.h>

void compute_row(int row_index, float input[6][8], float output[6][8])
{
    for (int j = 0; j < 8; j = j + 1)
    {
        /* Here is the 5-point stencil */
        const int right_column_index = (j + 1) % 8;
        const int left_column_index = (j + 8 - 1) % 8;
        const int top_row_index = row_index-1;
        const int bottom_row_index = row_index+1;
        output[row_index][j] = (input[row_index][j] +
                                input[row_index][left_column_index] +
                                input[row_index][right_column_index] +
                                input[top_row_index][j] +
                                input[bottom_row_index][j]);
    }
}

int main(int argc, char **argv)
{
    /* ==== CHALLENGE ====
     *
     * Uncomment the line and fix the MPI call to make this code work!
     * We want to use fork-join parallelism, so pick a more suitable
     * threading mode */
    /* Initialize the MPI environment and check */
    int provided, required = MPI_THREAD_FUNNELED;
    MPI_Init_thread(NULL, NULL, required, &provided);
    MPI_Comm comm = MPI_COMM_WORLD;

    /* If the program can't run, stop running */
    if (required != provided)
    {
        printf("Sorry, the MPI library does not provide "
               "this threading level! Aborting!\n");
        MPI_Abort(comm, 1);
    }

    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    if (size != 2)
    {
        if (rank == 0)
        {
            printf("Only two ranks is supported for this exercise, "
                    "please re-run with two ranks\n");
        }
        MPI_Finalize();
        return 0;
    }

    /* Prepare the initial values for this process */
    float local_data_set[4][8];
    printf("Local data set on rank %d was:\n", rank);
    for (int i = 0; i < 4; i = i + 1)
    {
        printf(" [ ");
        for (int j = 0; j < 8; j = j + 1)
        {
            /* Make sure the local data on each rank is different, so
             * that we see the communication works properly. */
            local_data_set[i][j] = 1*(rank + 1);
            if (j != 0)
            {
                printf(", ");
            }
            printf("%g", local_data_set[i][j]);
        }
        printf(" ]\n");
    }
    float working_data_set[6][8];
    for (int i = 0; i < 4; i = i + 1)
    {
        for (int j = 0; j < 8; j = j + 1)
        {
            /* Initialize the local part of the working data set */
            working_data_set[i+1][j] = local_data_set[i][j];
        }
    }

    /* Prepare to report whether the code is correct */
    int success = 1;

    /* Do the loop over heat-propagation steps */
    float next_working_data_set[6][8];
    float total, local_total, temporary_total;
    const int total_root_rank = 0;
    MPI_Request total_request = MPI_REQUEST_NULL;
    const int max_step = 10;
    for (int step = 0; step < max_step; step = step + 1)
    {
        int send_up_tag = 0, send_down_tag = 1;
        /* Prepare to receive the halo data */
        int source_rank = size-rank-1;
        MPI_Request sent_from_source[2];
        MPI_Irecv(working_data_set[5], 8, MPI_FLOAT, source_rank, send_up_tag, comm, &sent_from_source[0]);
        MPI_Irecv(working_data_set[0], 8, MPI_FLOAT, source_rank, send_down_tag, comm, &sent_from_source[1]);

        /* Prepare to send the border data */
        int destination_rank = size-rank-1;
        MPI_Request sent_to_destination[2];
        MPI_Isend(working_data_set[1], 8, MPI_FLOAT, destination_rank, send_up_tag, comm, &sent_to_destination[0]);
        MPI_Isend(working_data_set[4], 8, MPI_FLOAT, destination_rank, send_down_tag, comm, &sent_to_destination[1]);

        /* ==== CHALLENGE ====
         *
         * Uncomment and fix the arguments to the MPI call to make
         * this code work!
         *
         * Pass parameters to compute_row() in a way that each
         * iteration of the for loop does an equal part of the
         * local_work, ie rows 2 and 3 of the working_data_set.  You
         * may need to consult the parameter names of compute_row().
         */
        /* Do the local computation. OpenMP will distribute each
         * iteration to a different thread. */
        int local_work[] = {2, 3};
#pragma omp parallel for
        for (int k = 0; k != 2; k = k + 1)
        {
            compute_row(local_work[k], working_data_set, next_working_data_set);
        }
        /* Implied thread barrier here */

        /* Wait for the halo-exchange receives to complete */
        MPI_Wait(&sent_from_source[0], MPI_STATUS_IGNORE);
        MPI_Wait(&sent_from_source[1], MPI_STATUS_IGNORE);
    
        /* ==== CHALLENGE ====
         *
         * Uncomment and fix the arguments to the MPI call to make
         * this code work!
         *
         * Pass parameters to compute_row() in a way that each
         * iteration of the for loop does an equal part of the
         * local_work, ie rows 1 and 4 of the working_data_set.  You
         * may need to consult the parameter names of compute_row().
         */
        /* Do the non-local computation. OpenMP will distribute each
         * iteration to a different thread. */
        int non_local_work[] = {1, 4};
#pragma omp parallel for
        for (int k = 0; k != 2; k = k + 1)
        {
            compute_row(non_local_work[k], working_data_set, next_working_data_set);
        }
        /* Implied thread barrier here */

        /* Compute the total heat via non-blocking reduction */
        if (step % 5 == 4)
        {
            local_total = 0;
            for (int i = 1; i < 5; i = i + 1)
            {
                for (int j = 0; j < 8; j = j + 1)
                {
                    local_total += next_working_data_set[i][j];
                }
            }
            fprintf(stderr, "Doing an non-blocking reduction on step %d\n", step);
            MPI_Ireduce(&local_total, &temporary_total, 1, MPI_FLOAT, MPI_SUM, total_root_rank, comm, &total_request);
        }
        /* Wait for the most recent total heat reduction, 4 steps after it was started */
        if (step % 5 == 3 && total_request != MPI_REQUEST_NULL)
        {
            MPI_Wait(&total_request, MPI_STATUS_IGNORE);
            total = temporary_total;
            if (rank == total_root_rank)
            {
                fprintf(stderr, "Total after waiting at step %d was %g\n", step, total);
            }
        }
        if (rank == total_root_rank)
        {
            const float expected_total_value = (step < 8) ? 0 : 300000;
            if (total != expected_total_value)
            {
                success = 0;
                printf("Failed on step %d with total %g not matching expected %g\n",
                        step, total, expected_total_value);
            }
        }

        /* Wait for the halo-exchange sends to complete */
        MPI_Wait(&sent_to_destination[0], MPI_STATUS_IGNORE);
        MPI_Wait(&sent_to_destination[1], MPI_STATUS_IGNORE);

        /* Prepare to iterate */
        for (int i = 1; i < 5; i = i + 1)
        {
            for (int j = 0; j < 8; j = j + 1)
            {
                /* copy the output back to the input array */
                working_data_set[i][j] = next_working_data_set[i][j];
            }
        }
    }
    /* Now that we have left the main loop, we should wait for
     * the most recent total heat reduction to complete. */
    if (total_request != MPI_REQUEST_NULL)
    {
        MPI_Wait(&total_request, MPI_STATUS_IGNORE);
        total = temporary_total;
        if (rank == total_root_rank)
        {
            fprintf(stderr, "Total after waiting at step %d was %g\n",
                    max_step - 1, total);
        }
    }
    if (rank == total_root_rank)
    {
        const float expected_total_value = 9.375e+08;
        if (total != expected_total_value)
        {
            success = 0;
            printf("Failed on step %d with total %g not matching expected %g\n",
                    max_step - 1, total, expected_total_value);
        }
    }

    /* Report whether the code is correct */
    if (rank == total_root_rank)
    {
        if (success)
        {
            printf("SUCCESS on rank %d!\n", rank);
        }
        else
        {
            printf("Improvement needed before rank %d can report success!\n", rank);
        }
    }

    /* Clean up and exit */
    MPI_Finalize();
    return 0;
}
