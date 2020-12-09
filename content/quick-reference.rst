Quick Reference
---------------

.. glossary::

   alignment
   data alignment
      See also `Wikipedia <https://en.wikipedia.org/wiki/Data_structure_alignment>`_.

   intracommunicator
      An object managing a group of processes and a communication context.
      Processes in the communicator can perform message passing operations with
      each other, but are isolated from processes not in the communicator.

   intercommunicator
      A communicator for group-to-group communication.

   origin process
      In :term:`RMA`, the process invoking |term-MPI_Put| and |term-MPI_Get| to access another process's (the *target* process) window.

   target process
      In :term:`RMA`, the process whose window is accessed by |term-MPI_Put| and |term-MPI_Get| invoked by another process (the *origin* process)

   window
   memory window
   remote memory window
      Process-local memory allocated for :term:`RMA` operations. It is of implementation-dependent type ``MPI_Win``.
      Windows can be created with a variety of MPI functions:

      - |term-MPI_Win_create|
      - |term-MPI_Win_allocate|
      - |term-MPI_Win_allocate_shared|
      - |term-MPI_Win_create_dynamic|

   RMA
   remote memory access
   one-sided communication
      Foooo

   synchronization
      The necessary coordination of remote memory accesses. It can be *active* or *passive*.

   typemap
      Abstraction used to represent a datatypes in MPI. It is an associative
      array (map) with datatypes, as understood by MPI, as *keys* and
      displacements, in bytes, as *values*. The displacements are computed
      relative to the buffer the datatype describes.

      .. math::

         \textrm{Typemap} = \{ \textrm{Datatype}_{0}: \textrm{Displacement}_{0}, \ldots, \textrm{Datatype}_{n-1}: \textrm{Displacement}_{n-1} \}


Visual glossary
^^^^^^^^^^^^^^^

.. todo::

   Explain the graphical conventions for ``MPI_Send``, ``MPI_Recv``, ``MPI_Get``, ``MPI_Put`` etc

MPI functions
^^^^^^^^^^^^^

.. glossary::

   ``MPI_Comm_split``
      Split an existing communicator.

      .. code-block:: c

         int MPI_Comm_split(MPI_Comm comm,
                            int color,
                            int key,
                            MPI_Comm *newcomm)

      |MPI_Comm_split-implementors_docs|

   ``MPI_Type_get_extent``
       Foo

       .. code-block:: c

          int MPI_Type_get_extent(MPI_Datatype type,
                                  MPI_Aint *lb,
                                  MPI_Aint *extent)

       |MPI_Type_get_extent-implementors_docs|

   ``MPI_Type_size``
       Foo

       .. code-block:: c

          int MPI_Type_get_size(MPI_Datatype type,
                                int *size)

       |MPI_Type_size-implementors_docs|

   ``MPI_Pack``
       Pack data in a message. The message is in contiguous memory.

       .. code-block:: c

          int MPI_Pack(const void *inbuf,
                       int incount,
                       MPI_Datatype datatype,
                       void *outbuf,
                       int outsize,
                       int *position,
                       MPI_Comm comm)

       |MPI_Pack-implementors_docs|

   ``MPI_Unpack``
       Unpack a message to data in contiguous memory.

       .. code-block:: c

          int MPI_Unpack(const void *inbuf,
                         int insize,
                         int *position,
                         void *outbuf,
                         int outcount,
                         MPI_Datatype datatype,
                         MPI_Comm comm)

       |MPI_Unpack-implementors_docs|

   ``MPI_Type_create_struct``
       Foo
       This function replaces the *deprecated* ``MPI_Type_struct``.

       .. code-block:: c

          int MPI_Type_create_struct(int count,
                                     const int array_of_block_lengths[],
                                     const MPI_Aint array_of_displacements[],
                                     const MPI_Datatype array_of_types[],
                                     MPI_Datatype *newtype)

       |MPI_Type_create_struct-implementors_docs|

   ``MPI_Type_commit``
       Foo

       .. code-block:: c

          int MPI_Type_commit(MPI_Datatype *datatype)

       |MPI_Type_commit-implementors_docs|

   ``MPI_Type_contiguous``
       Foo

       .. code-block:: c

          int MPI_Type_contiguous(int count,
                                  MPI_Datatype oldtype,
                                  MPI_Datatype *newtype)

       |MPI_Type_contiguous-implementors_docs|

   ``MPI_Type_vector``
       Foo

       .. code-block:: c

          int MPI_Type_vector(int count,
                              int blocklength,
                              int stride,
                              MPI_Datatype oldtype,
                              MPI_Datatype *newtype)

       |MPI_Type_vector-implementors_docs|

   ``MPI_Type_indexed``
       Foo

       .. code-block:: c

          int MPI_Type_indexed(int count,
                               const int array_of_blocklengths[],
                               const int array_of_displacements[],
                               MPI_Datatype oldtype,
                               MPI_Datatype *newtype)

       |MPI_Type_indexed-implementors_docs|

   ``MPI_Type_create_hvector``
       foo

       |MPI_Type_create_hvector-implementors_docs|

   ``MPI_Type_create_hindexed``
       foo

       |MPI_Type_create_hindexed-implementors_docs|

   ``MPI_Type_free``
       foo

       |MPI_Type_free-implementors_docs|

   ``MPI_Get``
       Load data from a remote memory window.

       .. code-block:: c

          int MPI_Get(void *origin_addr,
                      int origin_count,
                      MPI_Datatype origin_datatype,
                      int target_rank,
                      MPI_Aint target_disp,
                      int target_count,
                      MPI_Datatype target_datatype,
                      MPI_Win win)

       |MPI_Get-implementors_docs|

   ``MPI_Put``
       Store data to a remote memory window.

       .. code-block:: c

          int MPI_Put(const void *origin_addr,
                      int origin_count,
                      MPI_Datatype origin_datatype,
                      int target_rank,
                      MPI_Aint target_disp,
                      int target_count,
                      MPI_Datatype target_datatype,
                      MPI_Win win)

       |MPI_Put-implementors_docs|

   ``MPI_Accumulate``
       Accumulate data into target process through remote memory access.

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

       |MPI_Accumulate-implementors_docs|

   ``MPI_Win_create``
       Foo

       .. code-block:: c

          int MPI_Win_create(void *base,
                             MPI_Aint size,
                             int disp_unit,
                             MPI_Info info,
                             MPI_Comm comm,
                             MPI_Win *win)

       |MPI_Win_create-implementors_docs|

   ``MPI_Win_allocate``
       Foo

       .. code-block:: c

          int MPI_Win_allocate(MPI_Aint size,
                               int disp_unit,
                               MPI_Info info,
                               MPI_Comm comm,
                               void *baseptr,
                               MPI_Win *win)

       |MPI_Win_allocate-implementors_docs|

   ``MPI_Win_allocate_shared``
       Foo

       .. code-block:: c

          int MPI_Win_allocate_shared(MPI_Aint size,
                                      int disp_unit,
                                      MPI_Info info,
                                      MPI_Comm comm,
                                      void *baseptr,
                                      MPI_Win *win)

       |MPI_Win_allocate_shared-implementors_docs|

   ``MPI_Win_create_dynamic``
       Foo

       .. code-block:: c

          int MPI_Win_create_dynamic(MPI_Info info,
                                     MPI_Comm comm,
                                     MPI_Win *win)

       |MPI_Win_create_dynamic-implementors_docs|

   ``MPI_Win_fence``
       Foo

       .. code-block:: c

          int MPI_Win_fence(int assert,
                            MPI_Win win)

       |MPI_Win_fence-implementors_docs|

   ``MPI_Win_post``
       Foo

       .. code-block:: c

          int MPI_Win_post(MPI_Group group,
                           int assert,
                           MPI_Win win)

       |MPI_Win_post-implementors_docs|

   ``MPI_Win_start``
       Foo

       .. code-block:: c

          int MPI_Win_start(MPI_Group group,
                            int assert,
                            MPI_Win win)

       |MPI_Win_start-implementors_docs|

   ``MPI_Win_complete``
       Foo

       .. code-block:: c

          int MPI_Win_complete(MPI_Win win)

       |MPI_Win_complete-implementors_docs|

   ``MPI_Win_wait``
       Foo

       .. code-block:: c

          int MPI_Win_wait(MPI_Win win)

       |MPI_Win_wait-implementors_docs|

   ``MPI_Win_lock``
       Foo

       .. code-block:: c

          int MPI_Win_lock(int lock_type,
                           int rank,
                           int assert,
                           MPI_Win win)

       |MPI_Win_lock-implementors_docs|

   ``MPI_Win_unlock``
       Foo

       .. code-block:: c

          int MPI_Win_unlock(int rank,
                             MPI_Win win)

       |MPI_Win_unlock-implementors_docs|

   ``MPI_Isend``
       Start a non-blocking send

       .. code-block:: c

          int MPI_Isend(const void* buf, int count, MPI_Datatype datatype,
                        int dest, int tag, MPI_Comm comm, MPI_Request *request)

       |MPI_Isend-implementors_docs|

   ``MPI_Irecv``
       Starts a non-blocking receive

       .. code-block:: c

          int MPI_Irecv(void* buf, int count, MPI_Datatype datatype,
                       int source, int tag, MPI_Comm comm, MPI_Request *request)

       |MPI_Irecv-implementors_docs|

   ``MPI_Wait``
       Return when the operation is complete

       .. code-block:: c

          int MPI_Wait(MPI_Request *request, MPI_Status *status)

       |MPI_Wait-implementors_docs|

   ``MPI_Waitany``
       Waits until exactly one operation completes

       .. code-block:: c

          int MPI_Waitany(int count, MPI_Request array_of_requests[],
                          int *index, MPI_Status *status)

       |MPI_Waitany-implementors_docs|

   ``MPI_Waitsome``
       Waits until at least one operation completes

       .. code-block:: c

          int MPI_Waitsome(int incount, MPI_Request array_of_requests[], int *outcount,
                           int array_of_indices[], MPI_Status array_of_statuses[])

       |MPI_Waitsome-implementors_docs|

   ``MPI_Waitall``
       Waits until all operations complete

       .. code-block:: c

          int MPI_Waitall(int count, MPI_Request array_of_requests[],
                          MPI_Status array_of_statuses[])

       |MPI_Waitall-implementors_docs|

   ``MPI_Test``
       Return immediately whether the operation is complete

       .. code-block:: c

          int MPI_Test(MPI_Request *request, int *flag, MPI_Status *status)

       |MPI_Test-implementors_docs|

   ``MPI_Testany``
       Returns immediately at most one operation has completed

       .. code-block:: c

          int MPI_Testany(int count, MPI_Request array_of_requests[],
                          int *index, int *flag, MPI_Status *status)

       |MPI_Testany-implementors_docs|

   ``MPI_Testsome``
       Like |term-MPI_Waitsome| but returns immediately

       .. code-block:: c

          int MPI_Testsome(int incount, MPI_Request array_of_requests[], int *outcount,
                           int array_of_indices[], MPI_Status array_of_statuses[])

       |MPI_Testsome-implementors_docs|

   ``MPI_Testall``
       Returns immediately whether all operations have completed

       .. code-block:: c

          int MPI_Testall(int count, MPI_Request array_of_requests[],
                          int *flag, MPI_Status array_of_statuses[])

       |MPI_Testall-implementors_docs|

   ``MPI_Init_thread``
       Initializes MPI and the threading environment within it. Should
       be preferred to ``MPI_Init`` by thread-aware applications.

       .. code-block:: c

          int MPI_Init_thread(int *argc, char **argv, int required, int *provided)

       |MPI_Init_thread-implementors_docs|
   
   ``MPI_Query_thread``
       Returns the current level of threading support.

       .. code-block:: c

          int MPI_Query_thread(int *provided)

       |MPI_Query_thread-implementors_docs|
   
   ``MPI_Is_thread_main``
       Returns whether the calling thread previously called |term-MPI_Init_thread|

       .. code-block:: c

          int MPI_Is_thread_main(int *flag)

       |MPI_Is_thread_main-implementors_docs|
   
   ``MPI_Ireduce``
       Non-blocking variant of TODO ``term-MPI_Reduce``

       .. code-block:: c

          int MPI_Ireduce(const void* sendbuf, void* recvbuf, int count,
                          MPI_Datatype datatype, MPI_Op op, int root,
                          MPI_Comm comm, MPI_Request *request)

       |MPI_Ireduce-implementors_docs|

   ``MPI_Barrier``
       Ensures all ranks arrive at this call before any of the proceeds
       past it.

       .. code-block:: c

          int MPI_Barrier(MPI_Comm comm)

       |MPI_Barrier-implementors_docs|

   ``MPI_Bcast``
       Sends data from one rank to all other ranks

       .. code-block:: c

            int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype,
                          int root, MPI_Comm comm)

       |MPI_Bcast-implementors_docs|

   ``MPI_Reduce``
       Combines data from all ranks using an operation and returns
       values to a single rank.

       .. code-block:: c

            int MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
                           MPI_Datatype datatype, MPI_Op op,
                           int root, MPI_Comm comm)

       |MPI_Reduce-implementors_docs|

   ``MPI_Scatter``
       Sends data from one rank to all other ranks

       .. code-block:: c

            int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                            void *recvbuf, int recvcount, MPI_Datatype recvtype,
                            int root, MPI_Comm comm)


       |MPI_Scatter-implementors_docs|

   ``MPI_Gather``
       Sends data from all ranks to a single rank

       .. code-block:: c

            int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                            void *recvbuf, int recvcount, MPI_Datatype recvtype,
                            int root, MPI_Comm comm)

       |MPI_Gather-implementors_docs|

   ``MPI_Allgather``
       Gathers data from all ranks and provides the same data to all ranks

       .. code-block:: c

            int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                              void *recvbuf, int recvcount, MPI_Datatype recvtype,
                              MPI_Comm comm)

       |MPI_Allgather-implementors_docs|

   ``MPI_Alltoall``
       Gathers data from all ranks and provides different parts of the
       data to different ranks.

       .. code-block:: c

            int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                             void *recvbuf, int recvcount, MPI_Datatype recvtype,
                             MPI_Comm comm)

       |MPI_Alltoall-implementors_docs|


.. TODO MPI_Send, MPI_Xsend, non-blocking forms
