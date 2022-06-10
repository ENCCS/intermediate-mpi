/* adapted from:
 * https://www.mcs.anl.gov/research/projects/mpi/usingmpi/examples-usingmpi/simplempi/monte-ex_c.html
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <mpi.h>

#define CHUNKSIZE 1000

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

  /* FIXME create checkers group */

  /* FIXME create checkers communicator */

  // handle the random number generation
  if (rank == rng) { /* I am the random number generator */
    // listen for requests from any source
    do {
      /* FIXME receive a request for random data  */
      MPI_Recv(&request, 1, MPI_INT, .., .., .., &status);
      if (request) {
        for (int i = 0; i < CHUNKSIZE; ++i) {
          rands[i] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
        /* FIXME send random data */
        MPI_Send(rands, .., .., .., .., ..);
      }
    } while (request > 0);
  } else { /* I am a checker process */
    // first thing, a checker process always requests fresh random data
    request = 1;
    done = in = out = 0;
    /* FIXME send a request for random data */
    MPI_Send(&request, 1, MPI_INT, .., .., ..);
    // set the number of samples processed to 0
    n_samples = 0;
    // check the random samples
    while (!done) {
      n_samples++;
      /* FIXME receive the random data */
      MPI_Recv(rands, .., .., .., .., .., ..);
      int i;
      for (i = 0; i < CHUNKSIZE-1; i+=2) {
        x = rands[i];
        y = rands[i+1];
        if (x * x + y * y < 1.0) {
          in++;
        } else {
          out++;
        }
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
      error = fabs(Pi - M_PI);

      // are we done?
      done = (error < epsilon || (totalin + totalout) > 100000000);
      request = (done) ? 0 : 1;

      // print current estimate and send a new request
      if (rank == 0) {
        printf("\rpi = %23.20f", Pi);
        /* FIXME send request for random data */
        MPI_Send(&request, .., .., .., .., ..);
      } else {
        if (request) {
          /* FIXME send request for random data */
          MPI_Send(&request, .., .., .., .., ..);
        }
      }
    }

    /* FIXME clean up communicator and group for checker processes */
  }

  // print results
  if (rank == 0) {
    printf("\npoints: %d\nin: %d, out: %d, <ret> to exit\n", totalin + totalout,
           totalin, totalout);
    getchar();
  }

  MPI_Finalize();

  return 0;
}
