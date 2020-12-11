#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mpi.h>

#define STRLEN 25

struct Pokemon {
  // name of pokemon attacking
  char name[STRLEN];
  // life points
  double life_points;
  // damage done by the attack
  int damage;
  // strength multiplier
  double multiplier;
};

int main(int argc, char *argv[]) {
  int rank;
  int size;

  struct Pokemon charizard;

  MPI_Init(&argc, &argv);

  MPI_Comm comm = MPI_COMM_WORLD;

  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);

  MPI_Datatype typesig[4] = {MPI_CHAR, MPI_DOUBLE, MPI_INT, MPI_DOUBLE};
  int block_lengths[4] = {STRLEN, 1, 1, 1};

  MPI_Aint base_address, displacements[4];

  MPI_Get_address(&charizard.name, &displacements[0]);
  base_address = displacements[0];
  displacements[0] = displacements[0] - base_address;

  MPI_Get_address(&charizard.life_points, &displacements[1]);
  displacements[1] = displacements[1] - base_address;

  MPI_Get_address(&charizard.damage, &displacements[2]);
  displacements[2] = displacements[2] - base_address;

  MPI_Get_address(&charizard.multiplier, &displacements[3]);
  displacements[3] = displacements[3] - base_address;

  MPI_Datatype mpi_pokemon;
  MPI_Type_create_struct(4, block_lengths, displacements, typesig,
                         &mpi_pokemon);

  MPI_Type_commit(&mpi_pokemon);

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

  MPI_Type_free(&mpi_pokemon);

  MPI_Finalize();

  return EXIT_SUCCESS;
}
