MPI and threads in practice
===========================

.. questions::

   - When should I consider writing hybrid MPI+OpenMP programs?
   - What should I look out for when writing hybrid MPI+OpenMP programs?

.. objectives::

   - Know to estimate the benefits before trying to write code for hybrid parallelism

Using fork-join parallelism
---------------------------

In fork-join parallelism, multiple threads are launched to collaborate
on work. Typically regions of parallelism alternate with regions where
only one thread works. This enables parallelism to be introduced
gradually, and only where profiling shows that it would be most
beneficial. In typical implementations, threads are kept idle between
parallel regions; this is more efficient than creating and destroying
them many times.

.. figure:: img/fork-join-parallelism.svg
   :align: center

   OpenMP is particularly suited for fork-join parallelism. Beware
   that each parallel region requires synchronization between threads,
   which can be costly. Further, the speed-up depends critically on
   the time spent in the single-threaded regions!

The simplest hybrid approach is often to do the MPI communication in
the regions that are single-threaded.

.. figure:: img/fork-join-with-mpi.svg
   :align: center

   Fork-join parallelism is a natural fit for ``MPI_THREAD_FUNNELED``
   where fairly simple code can be improved with thread parallelism.

``for`` loops in Fortan/C/C++ can be readily parallelised with ``#pragma
omp parallel``, so applications that already use MPI outside such loops
can be converted to hybrid parallelism fairly easily.

.. challenge::

   You can find a scaffold for the code in the
   ``content/code/day-4/01_threading-funneled`` folder.  A working solution is
   in the ``solution`` subfolder. It is quite similar to that for the earlier
   non-blocking code-along exercise. Try to compile with::

        mpicc -g -fopenmp -Wall -std=c11 threading-funneled.c -o threading-funneled

   #. When you have the code compiling, try to run with::

        mpiexec -np 2 ./threading-funneled

   #. Try to fix the code so that it compiles, runs, and reports success

.. solution::

   * One correct approach is::

        int provided, required = MPI_THREAD_FUNNELED;
        MPI_Init_thread(NULL, NULL, required, &provided);
        /* ... */
        int local_work[] = {2, 3};
        /* ... */
        compute_row(local_work[k], working_data_set, next_working_data_set);
        /* ... */
        int non_local_work[] = {1, 4};
        /* ... */
        compute_row(non_local_work[k], working_data_set, next_working_data_set);


Using OpenMP tasking with MPI
-----------------------------

.. figure:: img/stencil-with-tasking.svg
   :align: center

   Stencil code with halo exchange implemented with OpenMP
   tasking. One group of threads takes responsibility for the halo
   exchange and non-local stencil work. Another takes responsibility
   for the local work. The threads are split statically during each
   time step, but how many threads to assign to each part might be
   able to be tuned over the duration of the program.

.. challenge::

   You can find a scaffold for the code in the
   ``content/code/day-4/02_threading-multiple`` folder.  A working solution is in the
   ``solution`` subfolder. Try to compile with::

        mpicc -g -fopenmp -Wall -std=c11 threading-multiple.c -o threading-multiple

   #. When you have the code compiling, try to run with::

        OMP_NUM_THREADS=4 mpiexec -np 2 ./threading-multiple

   #. Unfortunately I haven't found the last bug in my use of OpenMP tasking,
      but you can see the kind of approach that can work, and the complexity
      it entails. Do this only when you really need to!


Setting the proper thread affinity
----------------------------------

Setting the affinity or the preferred location of threads in the hardware
is crucial for the performance of hybrid MPI+OpenMP applications specially in
modern architectures which are composed of several non-uniform memory access (NUMA)
nodes. 


.. figure:: img/kebnekaise.png
   :align: center

   Kebnekaise architecture contains two NUMA nodes and 14 cores per NUMA node.
   Also several levels of cache L1,L2, and L3 can be seen in this architecture.

In addition to the physical cores (28 per node on Kebnekaise), logical cores could be
available in your system but this option is usually turned-off in HPC systems.
In the case of Kebnekaise, only one thread can run on a physical core:


.. signature:: |System information|

   .. code-block:: c

      lscpu | grep -i 'core\|thread\|Socket'
      Thread(s) per core:              1
      Core(s) per socket:              14
      Socket(s):                       2





Tips for implementing hybrid MPI+OpenMP
---------------------------------------

* Demonstrate that you need more scaling to solve the problem.
  
* Know why you're adding hybrid parallelism... to access more memory,
  improve performance, reduce communication or a combination?

* Estimate how much improvement is available, based on existing performance
  measurements, e.g. profiling to find bottlenecks. If you don't know how,
  learn. Access to quality tools at HPC clusters are worth it!

* Are your external libraries using threading? How should you manage them?

* You have to introduce effective OpenMP parallelism to 90% of the
  execution time to get a good result.

* Start with master-only or funneled style. Migrate later if
  measurements suggest it.

* Initialize data structures inside OpenMP regions, to take advantage of
  "first-touch" policies needed with NUMA nodes.

* Make use of OpenMP’s conditional compilation features to ensure that
  the application can still be built without OpenMP.

* If the application makes use of derived datatypes to pack/unpack
  noncontiguous data, consider replacing these with user-level
  pack/unpack routines which can be parallelised with OpenMP.

* Learn about and use the OpenMP environment variables well

* Learn how to use the MPI launcher to place the ranks and their
  threads well. This is different for different applications.


See also
--------

* `Hybrid MPI-OpenMP best practices <http://www.intertwine-project.eu/sites/default/files/images/INTERTWinE_Best_Practice_Guide_MPI%2BOpenMP_1.2.pdf>`_
* `Kebnekaise https://www.hpc2n.umu.se/resources/hardware/kebnekaise`

.. keypoints::

   - Fork-join parallelism with ``MPI_THREAD_FUNNELED`` is a cheap way to get improvements, but the benefit is limited
   - More complex multi-threading can do a better job of overlapping communication and computation
