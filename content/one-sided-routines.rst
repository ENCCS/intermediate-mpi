.. _one-sided-routines:


One-sided communications: functions
===================================

.. questions::

   - What functions should you use for RMA?

.. objectives::

   - Learn how to create memory windows.
   - Learn how to access remote memory windows.

RMA anatomy
-----------

One-sided communication in MPI is achieved in three steps, which map onto three sets of functions:

Windows
  Make memory available on each process for remote memory accesses. We use
  *memory windows*, which are objects of type ``MPI_Win`` providing handles to
  remotely-accessible memory.  MPI provides 4 **collective** routines for the
  creation of memory windows:

  - |term-MPI_Win_allocate| allocates memory and creates the window object.
  - |term-MPI_Win_create| creates a window from already allocated memory.
  - |term-MPI_Win_allocate_shared| creates a window from already allocated MPI shared memory.
  - |term-MPI_Win_create_dynamic| creates a window from allocated memory, but
    the window-memory pairing is deferred.

  A handle of type ``MPI_Win`` manages memory made available for remote
  operations on *all ranks* in the communicator.
  Memory windows must be explicitly freed after use with |term-MPI_Win_free|.

Load/store
  Load/store/transform data in remote windows. We can identify an *origin* and a
  *target* process. At variance with two-sided communication, the origin process
  fully specifies the data transfer: where the data comes from and where it is
  going to. There are three main groups of MPI routines for this purpose:

  - **Put** |term-MPI_Put| and ``MPI_Rput``
  - **Get** |term-MPI_Get| and ``MPI_Rget``
  - **Accumulate** |term-MPI_Accumulate|, ``MPI_Raccumulate`` and variations thereof.

Synchronization
  Ensure that the data is available for remote memory accesses. The load/store
  routines are *non-blocking* and the programmer must take care that subsequent
  accesses are *safe* and *correct*.  How synchronization is achieved depends on
  the one-sided communication *paradigm* adopted:

  - **Active** if both origin and target processes play a role in the
    synchronization. This is indeed the message passing model of parallel
    computation.
  - **Passive** if the origin process orchestrates data transfer and
    synchronization. Conceptually, this is closely related to the shared memory
    model of parallel computation: the window is the shared memory in the
    communicator and every process can operate on it, seemingly independently of
    each other.

  There are three sets of routines currently available in MPI:

  - |term-MPI_Win_fence| this achieves synchronization in the **active target**
    communication paradigm.
  - |term-MPI_Win_start|, |term-MPI_Win_complete|, |term-MPI_Win_post|,
    |term-MPI_Win_wait| are also used in the **active target** communication
    paradigm.
  - |term-MPI_Win_lock|, |term-MPI_Win_unlock| which enables synchronization in
    the **passive target** paradigm.

  We will discuss synchronization further in the next episode :ref:`one-sided-sync`.


.. figure:: img/E02-RMA_timeline-coarse.svg
   :align: center

   The timeline of window creation, calls to RMA routines, and synchronization
   in an application which uses MPI one-sided communication.
   The creation of ``MPI_Win`` objects in each process in the communicator
   allows the execution of RMA routines. Each access to the window must be
   synchronized: to ensure safety and correctness of the application.
   Note that **any** interaction with the memory window **must** be protected by
   calls to synchronization routines: even local load/store and/or two-sided
   communication.
   The events in between synchronization calls are said to happen in *epochs*.


.. typealong:: RMA in action

   In this example, we will work with two processes:

   - Rank 1, will allocate a buffer and expose it as a window.
   - Rank 0, will get the values from this buffer.

   You can find a full working solution in the
   ``content/code/day-3/00_rma/solution`` folder.

   First of all, we create the buffer on all ranks. However, only rank 1 will
   fill it with some values. We will see that window creation is *collective*
   call for all ranks in the given communicator.

   .. code-block:: c

      int window_buffer[4] = {0};
      if (rank == 1) {
          window_buffer[0] = 42;
          window_buffer[1] = 88;
          window_buffer[2] = 12;
          window_buffer[3] = 3;
      }
      MPI_Win win;
      MPI_Win_create(&window_buffer, (MPI_Aint)4 * sizeof(int), sizeof(int),
                     MPI_INFO_NULL, comm, &win);

   Every rank has now a window, but only the window on rank 1 has values
   different from 0. Before doing anything on the window, we need to start an
   *access epoch*:

   .. code-block:: c

      MPI_Win_fence(0, win);

   Process 0 can now load the values into its local memory:

   .. code-block:: c

      int getbuf[4];
      if (rank == 0) {
        // Fetch the value from the MPI process 1 window
        MPI_Get(&getbuf, 4, MPI_INT, 1, 0, 4, MPI_INT, win);
      }

   We synchronize again once we are done with RMA operations: this access epoch
   is closed. This is needed even if subsequent accesses are local!

   .. code-block:: c

      MPI_Win_fence(0, win);

   Remember to free the window object!

   .. code-block:: c

      MPI_Win_free(&win);


.. discussion::

   - Are there similarities between one-sided and non-blocking communication? In
     which contexts would you prefer one over the other?


.. challenge:: Non-blocking vs RMA

   Can you re-express the code shown in the type-along with
   |term-MPI_Isend|/|term-MPI_Recv|?

   You can find a scaffold for the code in the
   ``content/code/day-3/01_rma-vs-nonblocking`` folder.  A working solution is in the
   ``solution`` subfolder.


Window creation
---------------

The creation of ``MPI_Win`` objects is a collective operation: each process in
the communicator will reserve the specified memory for remote memory accesses.

.. signature:: |term-MPI_Win_allocate|

   Use this function to *allocate* memory and *create* a window object out of it.

   .. code-block:: c

      int MPI_Win_allocate(MPI_Aint size,
                           int disp_unit,
                           MPI_Info info,
                           MPI_Comm comm,
                           void *baseptr,
                           MPI_Win *win)

We can expose an array of 10 ``double``-s for RMA with:

.. literalinclude:: code/snippets/allocate.c
   :language: c
   :lines: 6-15
   :dedent: 2

.. parameters::

   ``size``
       Size in bytes.
   ``disp_unit``
       Displacement units. If ``disp_unit = 1``, then displacements are computed
       in bytes. The use of displacement units can help with code readability
       and is essential for correctness on heterogeneous systems, where the
       sizes of the basic types might differ between processes.  See also
       :ref:`derived-datatypes`.
   ``info``
       An info object, which can be used to provide optimization hints to the
       MPI implementation. Using ``MPI_INFO_NULL`` is always correct.
   ``comm``
       The (intra)communicator.
   ``baseptr``
       The base pointer.
   ``win``
       The window object.


.. signature:: |term-MPI_Win_create|

   With this routine you can tell MPI what memory to expose as
   window. The memory must be already allocated and contiguous, since it will be
   specified in input as **base address plus size in bytes**.

   .. code-block:: c

      int MPI_Win_create(void *base,
                         MPI_Aint size,
                         int disp_unit,
                         MPI_Info info,
                         MPI_Comm comm,
                         MPI_Win *win)

What if the memory is not allocated? We advise to use |term-MPI_Alloc_mem|:

.. literalinclude:: code/snippets/alloc_mem+win_create.c
   :language: c
   :lines: 6-21
   :dedent: 2

You must explicitly call |term-MPI_Free_mem| to deallocate memory obtained
with |term-MPI_Alloc_mem|.

.. parameters::

   ``base``
       The base pointer.
   ``size``
       Size in bytes.
   ``disp_unit``
       Displacement units. If ``disp_unit = 1``, then displacements are computed
       in bytes. The use of displacement units can help with code readability
       and is essential for correctness on heterogeneous systems, where the
       sizes of the basic types might differ between processes.  See also
       :ref:`derived-datatypes`.
   ``info``
       An info object, which can be used to provide optimization hints to the
       MPI implementation. Using ``MPI_INFO_NULL`` is always correct.
   ``comm``
       The (intra)communicator.
   ``win``
       The window object.

.. note::

   - The memory window is usually a single array: the size of the window object
     then coincides with the size of the array.  If the base type of the array
     is a simple type, then the displacement unit is the size of that type,
     *e.g.* ``double`` and ``sizeof(double)``.  You should use a displacement
     unit of 1 otherwise.


.. challenge:: Window creation

   Let's look again at the initial example in the type-along. There we published
   an already allocated buffer as memory window. Use the examples above to
   figure out how to switch to using |term-MPI_Win_allocate|

   You can find a scaffold for the code in the
   ``content/code/day-3/02_rma-win-allocate`` folder.  A working solution is in the
   ``solution`` subfolder.


RMA operations
--------------

.. signature:: |term-MPI_Put|

   Store data from the **origin** process to the memory window of the **target**
   process.
   The origin process is the *source*, while the target process is the
   *destination*.

   .. code-block:: c

      int MPI_Put(const void *origin_addr,
                  int origin_count,
                  MPI_Datatype origin_datatype,
                  int target_rank,
                  MPI_Aint target_disp,
                  int target_count,
                  MPI_Datatype target_datatype,
                  MPI_Win win)


.. signature:: |term-MPI_Get|

   Load data from the memory window of the **target** process to the **origin**
   process.
   The origin process is the *destination*, while the target process is the
   *source*.

   .. code-block:: c

      int MPI_Get(void *origin_addr,
                  int origin_count,
                  MPI_Datatype origin_datatype,
                  int target_rank,
                  MPI_Aint target_disp,
                  int target_count,
                  MPI_Datatype target_datatype,
                  MPI_Win win)

.. parameters::

   Both |term-MPI_Put| and |term-MPI_Get| are *non-blocking*: they are completed
   by a call to synchronization routines.
   The two functions have the same argument list. Similarly to |term-MPI_Send|
   and |term-MPI_Recv|, the data is specified by the triplet of address, count,
   and datatype.
   For the data at the *origin* process this is: ``origin_addr``,
   ``origin_count``, ``origin_datatype``.
   On the *target* process, we describe the buffer in terms of displacement,
   count, and datatype: ``target_disp``, ``target_count``, ``target_datatype``.
   The address of the buffer on the target process is computed using the base
   address and displacement unit of the ``MPI_Win`` object:

   .. code-block:: c

      target_addr = win_base_addr + target_disp * disp_unit

   With |term-MPI_Put|, the ``origin`` triplet specifies the **local send
   buffer**; while with |term-MPI_Get| it specifies the **local receive
   buffer**.
   The ``target_rank`` parameter is, as the name suggests, the rank of the
   target process in the communicator.


.. challenge:: Using |term-MPI_Put|

   Reorganize the sample code of the previous exercise such that rank 1 *stores*
   values into rank 0 memory window with |term-MPI_Put|, rather than rank 0
   *loading* them with |term-MPI_Get|.

   You can find a scaffold for the code in the
   ``content/code/day-3/03_rma-put`` folder.  A working solution is in the
   ``solution`` subfolder.

.. signature:: |term-MPI_Accumulate|

   Store data from the **origin** process to the memory window of the **target**
   process *and* combine it using one the predefined MPI reduction operations.

   .. code-block:: c

      int MPI_Accumulate(const void *origin_addr,
                         int origin_count,
                         MPI_Datatype origin_datatype,
                         int target_rank,
                         MPI_Aint target_disp,
                         int target_count,
                         MPI_Datatype target_datatype,
                         MPI_Op op,
                         MPI_Win win)

   The argument list to |term-MPI_Accumulate| is the same as for |term-MPI_Put|,
   with the addition of the ``op`` parameter with type ``MPI_Op``, which
   specifies which reduction operation to execute on the target process.
   This routine is **elementwise atomic**: accesses from multiple processes will
   be serialized in some order and no race conditions can thus occur.  You still
   need to exercise care though: reductions are only deterministic if the
   operation is *associative* and *commutative* for the given datatype.  For
   example, ``MPI_SUM`` and ``MPI_PROD`` are *neither* associative *nor*
   commutative for floating point numbers!


.. challenge:: Using |term-MPI_Accumulate|

   You can find a scaffold for the code in the
   ``content/code/day-3/04_rma-accumulate`` folder.
   Follow the prompts and complete the function calls to:

   1. Create a window object from an allocated buffer:

      .. code-block::

         int buffer = 42;

   2. Let each process accumulate its rank in the memory window of the process
      with rank 0. We want to obtain the sum of the accumulating values.

   With 2 processes, you should get the following output to screen:

   .. code-block::

      [MPI process 0] Value in my window_buffer before MPI_Accumulate: 42.
      [MPI process 1] I accumulate data 1 in MPI process 0 window via MPI_Accumulate.
      [MPI process 0] Value in my window_buffer after MPI_Accumulate: 43.

   A working solution is in the ``solution`` subfolder.

Other routines for RMA operations are:

Request-based variants
   These routines return a handle of type ``MPI_Request`` and synchronization
   can be achieved with ``MPI_Wait``.

     - ``MPI_Rget``
     - ``MPI_Rput``
     - ``MPI_Raccumulate``
     - ``MPI_Rget_accumulate``

Specialized accumulation variants
   These functions perform specialized accumulations, but are conceptually
   similar to |term-MPI_Accumulate|.

     - ``MPI_Get_accumulate``
     - ``MPI_Fetch_and_op``
     - ``MPI_Compare_and_swap``


.. challenge:: Describe the sequence MPI calls connecting the before and after schemes.

   #. .. figure:: img/E02-win_allocate.svg

      A. Window creation with |term-MPI_Win_allocate|.
      B. Window creation with |term-MPI_Win_create| followed by |term-MPI_Alloc_mem|.
      C. Dynamic window creation with |term-MPI_Win_create_dynamic|.
      D. Memory allocation with |term-MPI_Alloc_mem| followed by window creation |term-MPI_Win_create|.

   #. .. figure:: img/E02-win_create_put.svg

      A. Window creation with |term-MPI_Win_allocate| and |term-MPI_Get| from *origin process 2* to *target process 1*.
      B. Window creation with |term-MPI_Win_create_dynamic| and |term-MPI_Put| from *origin process 1* to *target process 2*.
      C. Window creation with |term-MPI_Win_create| and |term-MPI_Get| from *origin process 1* to *target process 2*.
      D. Window creation with |term-MPI_Win_create| and |term-MPI_Put| from *origin process 2* to *target process 1*.

.. solution::

   #. Both options **A** and **D** are correct. With option **A**, we let MPI
      allocate memory on each process *and* create a ``MPI_Win`` window object.
      With option **C**, the memory allocation and window object creation are
      decoupled and managed by the programmer. If you have the choice, option **A**
      should be preferred: the MPI library might be able to better optimize window
      creation.
   #. Option **D** is correct. The memory is already allocated on each process,
      maybe through use of |term-MPI_Alloc_mem|, and the window can be created
      with a call to |term-MPI_Win_create|. The subsequent data movement is a
      remote *store* operation. The call |term-MPI_Put| is issued by process 2,
      the *origin* process, to store its ``C`` variable to the memory window of
      process 1, the *target* process.

See also
--------

* The lecture covering MPI RMA from EPCC is available
  `here <http://www.archer.ac.uk/training/course-material/2020/01/advMPI-imperial/Slides/L07-Intro%20to%20RMA.pdf>`_
* Chapter 3 of the **Using Advanced MPI** by William Gropp *et al.* :cite:`Gropp2014-dz`


.. keypoints::

   - The MPI model for remote memory accesses.
   - Window objects and memory windows.
   - Timeline of RMA and the importance of synchronization.
