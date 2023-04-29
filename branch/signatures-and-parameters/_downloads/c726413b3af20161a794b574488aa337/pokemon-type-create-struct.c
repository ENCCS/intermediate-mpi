#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#define STRLEN 25

/* FIXME Declare a Pokemon struct containing name, life_points, damage, and multiplier fields */
struct Pokemon {
  // name of pokemon attacking
  // life points
  // damage done by the attack
  // strength multiplier
};

int main(int argc, char *argv[]) {
  int rank;
  int size;

  struct Pokemon charizard;

  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  /* FIXME What is the typesignature for Pokemon */
  MPI_Datatype typesig ..;
  /* FIXME What are the block lenghts? */
  int block_lengths ..;

  /* FIXME What are the displacements? Remember, they are relative with respect to the first field! */
  MPI_Aint base_address, displacements[4];

  MPI_Get_address(.., ..);

  /* FIXME Create the datatype */
  MPI_Datatype mpi_pokemon;

  /* FIXME Commit the type */

  if (rank == 0) {
    sprintf(charizard.name, "Charizard");
    charizard.life_points = 180.0;
    charizard.damage = 60;
    charizard.multiplier = 0.89;

    MPI_Bcast(&charizard, 1, mpi_pokemon, 0, comm);
  } else {
    // matching broadcast on all other processes.
    MPI_Bcast(&charizard, 1, mpi_pokemon, 0, comm);

    // did we get it right?
    printf("rank %d:\n", rank);
    printf("  pokemon = %s\n", charizard.name);
    printf("  life_points = %2.2f\n", charizard.life_points);
    printf("  damage = %d\n", charizard.damage);
    printf("  multiplier = %2.2f\n", charizard.multiplier);
  }

  /* FIXME free the type */

  MPI_Finalize();

  return EXIT_SUCCESS;
}
