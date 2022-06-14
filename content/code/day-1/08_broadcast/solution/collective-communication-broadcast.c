#include <stdio.h>

#include <mpi.h>

int main(int argc, char **argv) {
  /* Initialize the MPI environment and report */
  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int rank, size;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);

  const int rank_of_root = 0;

  /* Prepare the values to broadcast */
  int expected_values[2] = {100, -1000};

  int values_to_broadcast[2] = {0, 0};
  if (rank == rank_of_root) {
    values_to_broadcast[0] = expected_values[0];
    values_to_broadcast[1] = expected_values[1];
  }

  /* Report the state before the broadcast */
  printf("On rank %d, pre-broadcast values were [%d, %d]\n", rank,
         values_to_broadcast[0], values_to_broadcast[1]);

  /* Do the broadcast */
  MPI_Bcast(values_to_broadcast, 2, MPI_INT, rank_of_root, comm);

  /* Report the state after the broadcast */
  printf("On rank %d, broadcast values were [%d, %d]\n", rank,
         values_to_broadcast[0], values_to_broadcast[1]);

  int reduced_values[2];
  MPI_Reduce(values_to_broadcast, reduced_values, 2, MPI_INT, MPI_SUM,
             rank_of_root, comm);

  /* Report the state after the reduction */
  if (rank == rank_of_root) {
    printf("On rank %d, reduced values were [%d, %d]\n", rank,
           reduced_values[0], reduced_values[1]);
  }

  /* Report whether the code is correct */
  int success = ((values_to_broadcast[0] == expected_values[0]) &&
                 (values_to_broadcast[1] == expected_values[1]));

  /* Success on the root rank also means checking the reduction */
  if (rank == rank_of_root) {
    success = success && ((reduced_values[0] == expected_values[0] * size) &&
                          (reduced_values[1] == expected_values[1] * size));
  }

  if (success) {
    printf("SUCCESS on rank %d!\n", rank);
  } else {
    printf("Improvement needed before rank %d can report success!\n", rank);
  }

  /* Clean up and exit */
  MPI_Finalize();

  return 0;
}
