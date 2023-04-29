/* adapted from:
 * https://www.mcs.anl.gov/research/projects/mpi/usingmpi/examples-usingmpi/simplempi/monte-ex_c.html
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define CHUNKSIZE 1000

#define PI 3.141592653589793238462643

/* message tags */
#define REQUEST 1
#define REPLY 2

int main(int argc, char *argv[]) {
  // number of Monte Carlo samples
  int n_samples;
  // counter for the number of samples inside and outside the circle
  int in, out;
  // total tally of samples inside and outside the circle
  int totalin, totalout;
  // coordinates of the random point
  double x, y;
  // current estimate of pi
  double Pi;
  // error and user-provided threshold
  double error, epsilon;
  // whether user-provided threshold was met
  int done;
  // random data
  double rands[CHUNKSIZE];
  int size, rank, rng;
  int request;
  int ranks[1];
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm world = MPI_COMM_WORLD;

  MPI_Comm_size(world, &size);
  MPI_Comm_rank(world, &rank);

  // we use the last process as the random number server
  rng = size - 1;

  // read user input
  if (rank == 0) {
    if (argc < 2) {
      fprintf(stderr, "Usage: %s epsilon\n", argv[0]);
      MPI_Abort(world, 1);
    }
    sscanf(argv[1], "%lf", &epsilon);
  }

  // let every process know what the threshold is
  // the collective operation will be discussed later on
  MPI_Bcast(&epsilon, 1, MPI_DOUBLE, 0, world);

  // create checkers_g group
  MPI_Group world_group, checkers_g;
  MPI_Comm_group(world, &world_group);
  ranks[0] = rng;
  MPI_Group_excl(world_group, 1, ranks, &checkers_g);

  // create checkers communicator
  MPI_Comm checkers;
  MPI_Comm_create(world, checkers_g, &checkers);
  MPI_Group_free(&checkers_g);

  // handle the random number generation
  if (rank == rng) { /* I am the random number generator */
    // listen for requests from any source
    do {
      MPI_Recv(&request, 1, MPI_INT, MPI_ANY_SOURCE, REQUEST, world, &status);
      if (request) {
        for (int i = 0; i < CHUNKSIZE; ++i) {
          rands[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
        MPI_Send(rands, CHUNKSIZE, MPI_DOUBLE, status.MPI_SOURCE, REPLY, world);
      }
    } while (request > 0);
  } else { /* I am a checker process */
    // first thing, a checker process always requests fresh random data
    request = 1;
    done = in = out = 0;
    MPI_Send(&request, 1, MPI_INT, rng, REQUEST, world);
    // set the number of samples processed to 0
    n_samples = 0;
    // check the random samples
    while (!done) {
      n_samples++;
      request = 1;
      MPI_Recv(rands, CHUNKSIZE, MPI_DOUBLE, rng, REPLY, world,
               MPI_STATUS_IGNORE);
      for (int i = 0; i < CHUNKSIZE;) {
        x = rands[i++];
        y = rands[i++];
        if (x * x + y * y < 1.0)
          in++;
        else
          out++;
      }

      // total tally of points inside the circle
      // the collective operation will be discussed later on
      MPI_Allreduce(&in, &totalin, 1, MPI_INT, MPI_SUM, checkers);

      // total tally of points outside the circle
      // the collective operation will be discussed later on
      MPI_Allreduce(&out, &totalout, 1, MPI_INT, MPI_SUM, checkers);

      // compute pi
      Pi = (4.0 * totalin) / (totalin + totalout);

      // check error
      error = fabs(Pi - PI);

      // are we done?
      done = (error < epsilon || (totalin + totalout) > 100000000);
      request = (done) ? 0 : 1;

      // print current estimate and send a new request
      if (rank == 0) {
        printf("\rpi = %23.20f", Pi);
        MPI_Send(&request, 1, MPI_INT, rng, REQUEST, world);
      } else {
        if (request)
          MPI_Send(&request, 1, MPI_INT, rng, REQUEST, world);
      }
    }

    // clean up!
    MPI_Comm_free(&checkers);
  }

  // print results
  if (rank == 0) {
    printf("\npoints: %d\nin: %d, out: %d, <ret> to exit\n", totalin + totalout,
           totalin, totalout);
    getchar();
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
