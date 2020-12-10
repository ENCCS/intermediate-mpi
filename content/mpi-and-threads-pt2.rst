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

`for` loops in Fortan/C/C++ can be readily parallelised with `#pragma
omp parallel`, so applications that already use MPI outside such loops
can be converted to hybrid parallelism fairly easily.

.. challenge::

   TODO Make MPI work within a fork-join form of the stencil application

.. solution::

   TODO

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

   TODO Make MPI work within a tasking form in the stencil application

.. solution::

   TODO

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

.. keypoints::

   - Fork-join parallelism with ``MPI_THREAD_FUNNELED`` is a cheap way to get improvements, but the benefit is limited
   - More complex multi-threading can do a better job of overlapping communication and computation
