#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#define STRLEN 25

int main(int argc, char *argv[]) {
  int rank;
  int size;
  // marker used by MPI_Pack and MPI_Unpack
  int position;

  // name of pokemon attacking
  char pokemon[STRLEN];
  // life points
  int life_points;
  // damage done by the attack
  int damage;
  // strength multiplier
  double multiplier;

  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  int sz1, sz2, sz3, sz4;
  MPI_Pack_size(STRLEN, MPI_CHAR, comm, &sz1);

  MPI_Pack_size(1, MPI_DOUBLE, comm, &sz2);

  MPI_Pack_size(1, MPI_INT, comm, &sz3);

  MPI_Pack_size(1, MPI_DOUBLE, comm, &sz4);

  int bufsiz = sz1 + sz2 + sz3 + sz4;
  // buffer for the message
  char *message = (char *)malloc((unsigned)bufsiz);

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  if (rank == 0) {
    sprintf(pokemon, "Blastoise");
    life_points = 150;
    damage = 40;
    multiplier = 1.32;

    position = 0;
    // we're ready to do some packing!
    MPI_Pack(&pokemon, STRLEN, MPI_CHAR, message, sz1, &position, comm);
    // where is position now?
    printf("packed pokemon, position = %d\n", position);

    MPI_Pack(&life_points, 1, MPI_INT, message, sz1 + sz2, &position, comm);
    printf("packed life_points, position = %d\n", position);

    MPI_Pack(&damage, 1, MPI_INT, message, sz1 + sz2 + sz3, &position, comm);
    printf("packed damage, position = %d\n", position);

    MPI_Pack(&multiplier, 1, MPI_DOUBLE, message, sz1 + sz2 + sz3 + sz4,
             &position, comm);
    printf("packed multiplier, position = %d\n", position);

    // let it be known that a move was made!
    MPI_Bcast(message, bufsiz, MPI_PACKED, 0, comm);
  } else {
    // matching broadcast on all other processes.
    MPI_Bcast(message, bufsiz, MPI_PACKED, 0, comm);

    position = 0;
    // let's get to unpacking
    // !!! the length of the string MUST be known
    MPI_Unpack(message, sz1, &position, &pokemon, STRLEN, MPI_CHAR, comm);
    printf("unpacked pokemon, position = %d\n", position);

    MPI_Unpack(message, sz1 + sz2, &position, &life_points, 1, MPI_INT, comm);
    printf("unpacked life_points, position = %d\n", position);

    MPI_Unpack(message, sz1 + sz2 + sz3, &position, &damage, 1, MPI_INT, comm);
    printf("unpacked damage, position = %d\n", position);

    MPI_Unpack(message, sz1 + sz2 + sz3 + sz4, &position, &multiplier, 1,
               MPI_DOUBLE, comm);
    printf("unpacked multiplier, position = %d\n", position);

    // did we get it right?
    printf("rank %d:\n", rank);
    printf("  pokemon = %s\n", pokemon);
    printf("  life_points = %d\n", life_points);
    printf("  damage = %d\n", damage);
    printf("  multiplier = %2.2f\n", multiplier);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
