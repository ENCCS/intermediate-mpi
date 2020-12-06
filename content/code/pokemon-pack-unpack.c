#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#define STRLEN 25

int main(int argc, char *argv[]) {
  int rank;
  int size;
  /* TODO explain what the purpose of position is */
  int position;

  // name of pokemon attacking
  char pokemon[STRLEN];
  // life points
  double life_points;
  // damage done by the attack
  int damage;
  // strength multiplier
  double multiplier;

  // buffer for the message
  // we set it to BUFSIZ (defined in stdio.h) assuming that's big enough!
  char message[BUFSIZ];

  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  if (rank == 0) {
    /* FIXME define the data for the move in the game */

    /* FIXME pack the data into the message buffer with calls to MPI_Pack */

    // let it be known that a move was made!
    /* FIXME set the MPI_Datatype parameter to the correct one for a packed message */
    MPI_Bcast(message, BUFSIZ, xxx, 0, comm);
  } else {
    // matching broadcast on all other processes.
    /* FIXME set the MPI_Datatype parameter to the correct one for a packed message */
    MPI_Bcast(message, BUFSIZ, xxx, 0, comm);

    /* FIXME unpack the data from the message buffer with calls to MPI_Unpack */
    position = 0;

    // did we get it right?
    printf("rank %d:\n", rank);
    printf("  pokemon = %s\n", pokemon);
    printf("  life_points = %2.2f\n", life_points);
    printf("  damage = %d\n", damage);
    printf("  multiplier = %2.2f\n", multiplier);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
