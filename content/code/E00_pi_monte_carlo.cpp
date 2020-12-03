#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <random>

#include <mpi.h>

// size of the array of random numbers
#define CHUNKSIZE 1000
// tags for communication
#define REQUEST 1
#define REPLY 2

int main(int argc, char **argv) {
  // initialize variables
  int iter, maxsamples;
  int in, out, iters, max, ix, iy, ranks[1], done, temp;
  double x, y, pi, error, epsilon;
  int numprocs, my_id, totalin, totalout;
  std::array<double, CHUNKSIZE> rands;
  int request;
  MPI_Comm helpers;
  MPI_Group world_group, helper_group;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  auto world = MPI_COMM_WORLD;
  MPI_Comm_size(world, &numprocs);
  if (numprocs == 1) {
    std::cerr << "This program needs at least 2 processes!" << std::endl;
    MPI_Abort(world, 1);
  }
  MPI_Comm_rank(world, &my_id);
  auto main = numprocs - 1;
  if (my_id == 0) {
    if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " epsilon maxsamples" << std::endl;
      MPI_Abort(world, 1);
    } else {
      std::cout << "# processes is: " << numprocs << std::endl;
      std::sscanf(argv[1], "%lf", &epsilon);
      std::sscanf(argv[2], "%d", &maxsamples);
    }
  }
  MPI_Bcast(&epsilon, 1, MPI_DOUBLE, 0, world);

  MPI_Comm_group(world, &world_group);
  ranks[0] = main;
  MPI_Group_excl(world_group, 1, ranks, &helper_group);
  MPI_Comm_create(world, helper_group, &helpers);
  MPI_Group_free(&world_group);
  MPI_Group_free(&helper_group);


  if (my_id == main) { // main process
    // Will be used to obtain a seed for the random number engine
    std::random_device rd;
    // Mersenne twister engine with seed from the random device
    std::mt19937 gen(rd());
    // Uniform distribution of floating-poing double precision numbers in [-1,
    // 1)
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    std::cout << "Now I have the PRNG" << std::endl;
    do {
      std::cout << my_id << " Any requests?" << std::endl;
      MPI_Recv(&request, 1, MPI_INT, MPI_ANY_SOURCE, REQUEST, world, &status);
      if (request) { // fill the array of random numbers
        std::cout << "Yes, I have a request" << std::endl;
        for (auto i = 0; i < CHUNKSIZE; ++i) {
          rands[i] = dis(gen);
        }
        MPI_Send(rands.data(), CHUNKSIZE, MPI_DOUBLE, status.MPI_SOURCE, REPLY,
                 world);
        std::cout << "request satisfied" << std::endl;
      }
    } while (request > 0);
  } else { // helper processes
    request = 1;
    done = in = out = 0;
    MPI_Send(&request, 1, MPI_INT, main, REQUEST, world);
    iter = 0;
    while (!done) {
      iter++;
      request = 1;
      MPI_Recv(rands.data(), CHUNKSIZE, MPI_DOUBLE, main, REPLY, world,
               MPI_STATUS_IGNORE);
      for (auto i = 0; i < CHUNKSIZE;) {
        x = rands[i++];
        y = rands[i++];
        if (x * x + y * y < 1.0) {
          in++;
        } else {
          out++;
        }
      }
      MPI_Allreduce(&in, &totalin, 1, MPI_INT, MPI_SUM, helpers);
      MPI_Allreduce(&out, &totalout, 1, MPI_INT, MPI_SUM, helpers);
      pi = (4.0 * totalin) / (totalin + totalout);
      error = std::fabs(pi - M_PI);
      done = (error < epsilon || (totalin + totalout) > maxsamples);
      request = done ? 0 : 1;
      if (my_id == 0) {
        std::printf("\rpi = %2.12f [Monte Carlo estimate]; pi = %2.12f "
                    "[Exact]; |Delta| = %2.6e",
                    pi, M_PI, error);
        MPI_Send(&request, 1, MPI_INT, main, REQUEST, world);
      } else {
        if (request)
          MPI_Send(&request, 1, MPI_INT, main, REQUEST, world);
      }
    }
    MPI_Comm_free(&helpers);
  }

  if (my_id == 0) {
    std::printf("\npoints = %d; in = %d; out = %d [maxsamples = %d]\n",
                totalin + totalout, totalin, totalout, maxsamples);
  }

  MPI_Finalize();

  return EXIT_SUCCESS;
}
