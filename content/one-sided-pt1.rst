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


.. challenge:: What kind of operations are being carried out?

   #. .. figure:: img/E02-mpi_put.svg

      A. Process 1 calls |term-MPI_Put| with process 0 as target.
      B. Process 1 calls |term-MPI_Send| with process 0 as receiver.
      C. Process 0 calls |term-MPI_Get| with process 1 as target.
      D. Process 1 calls |term-MPI_Get| with  process 0 as target.

   #. .. figure:: img/E02-mpi_send_mpi_recv.svg

      A. Process 0 calls |term-MPI_Send| with process 1 as receiver. Process 1 matches the call with |term-MPI_Get|.
      B. Process 0 calls |term-MPI_Put|. Process 1 retrieves the data with |term-MPI_Recv|.
      C. Process 0 calls |term-MPI_Send| matched with a call to |term-MPI_Recv| by process 1.
      D. None of the above.

   #. .. figure:: img/E02-mpi_get.svg

      A. Process 1 calls |term-MPI_Put| with process 0 as target.
      B. Process 1 calls |term-MPI_Recv| with process 0 as sender.
      C. Process 0 calls |term-MPI_Get| with process 1 as target.
      D. Process 1 calls |term-MPI_Get| with  process 0 as target.

   #. .. figure:: img/E02-local_load_store.svg

      A. Process 1 calls |term-MPI_Put| with process 0 as target.
      B. Process 0 loads a variable from its window to its local memory.
      C. Process 0 calls |term-MPI_Get| with process 1 as target.
      D. Process 0 stores a variable from its local memory to its window.

   #. .. figure:: img/E02-win_mpi_send_mpi_recv.svg

      A. Process 0 calls |term-MPI_Send| with process 1 as receiver. Process 1 matches the call with |term-MPI_Get|.
      B. Process 1 calls |term-MPI_Get| with process 0 as target.
      C. None of the options.
      D. Process 0 calls |term-MPI_Send| matched with a call to |term-MPI_Recv| by process 1.

   #. .. figure:: img/E02-invalid.svg

      A. Process 0 calls |term-MPI_Send| matched with a call to |term-MPI_Recv| by process 1.
      B. This operation is not valid in MPI.
      C. Process 1 calls |term-MPI_Get| with process 0 as target.
      D. Process 0 calls |term-MPI_Put| with process 1 as target.


.. solution::

   #. **A** is the correct answer. Process 1 initiates the one-sided memory access,
      in order to *put* (*store*) the contents of its local memory to the remote memory
      window opened on process 0.
   #. **D** is the correct answer. Process 1 initiates the one-sided memory
      access in order to *get* (*load*) the contents of the remote memory window on
      process 0 to its local memory.
   #. **C** is the correct answer. This is the standard, blocking two-sided
      communication pattern in MPI.
   #. Both **B** and **D** are valid answers. The figure depicts a memory
      operation *within* process 0, which does not involve communication with
      any other process and thus pertains the programming language and not MPI.
   #. **D** is the correct answer. This is the standard, blocking two-sided
      communication pattern in MPI: it does not matter whether the message stems
      from memory local to process 0 or its remotely accessible window.
   #. **C** is the correct answer. Different processes can only interact with
      explicit two-sided communication or by first publishing to their remotely
      accessible window.


See also
--------

* The lecture covering MPI RMA from EPCC is available
  `here <http://www.archer.ac.uk/training/course-material/2020/01/advMPI-imperial/Slides/L07-Intro%20to%20RMA.pdf>`_
* Chapter 3 of the **Using Advanced MPI** by William Gropp *et al.* :cite:`Gropp2014-dz`


.. keypoints::

   - The MPI model for remote memory accesses.
   - The basic routines to publish remotely accessible memory.
   - The basic routines to modify remote memory windows.
