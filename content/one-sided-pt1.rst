One-sided communication: basic concepts
=======================================

.. questions::

   - How can we optimize communication?

.. objectives::

   - Learn about functions for remote-memory access (RMA)
   - RMA: |term-MPI_Get|, |term-MPI_Put|, |term-MPI_Accumulate|
   - Windows: |term-MPI_Win_create|, |term-MPI_Win_allocate|, |term-MPI_Win_allocate_shared|, |term-MPI_Win_create_dynamic|


Topic introduction here

You really want to browse this page alongside the source of it, to see
how this is implemented.  See the links at the to right of the page.


.. challenge:: Calling |term-MPI_Put| and |term-MPI_Get|

   1. What kind of remote memory operation is being carried out?

      .. figure:: img/E02-mpi_put.svg

      A. Process 1 calls |term-MPI_Put| with process 0 as target.
      B. Process 1 calls |term-MPI_Send| with process 0 as receiver.
      C. Process 0 calls |term-MPI_Get| with process 1 as target.
      D. Process 1 calls |term-MPI_Get| with  process 0 as target.

   1. What kind of remote memory operation is being carried out?

      .. figure:: img/E02-mpi_get.svg

      A. Process 1 calls |term-MPI_Put| with process 0 as target.
      B. Process 1 calls |term-MPI_Recv| with process 0 as sender.
      C. Process 0 calls |term-MPI_Get| with process 1 as target.
      D. Process 1 calls |term-MPI_Get| with  process 0 as target.


.. solution::

   1. A is the correct answer. Process 1 initiates the one-sided memory access
      in order to copy the contents of its local memory to the remote memory
      window opened on process 0.


See also
--------

* The lecture covering MPI RMA from EPCC is available
  `here <http://www.archer.ac.uk/training/course-material/2020/01/advMPI-imperial/Slides/L07-Intro%20to%20RMA.pdf>`_
* Chapter 3 of the **Using Advanced MPI** by William Gropp *et al.* :cite:`Gropp2014-dz`


.. keypoints::

   - The MPI model for remote memory accesses.
   - The basic routines to publish remotely accessible memory.
   - The basic routines to modify remote memory windows.
