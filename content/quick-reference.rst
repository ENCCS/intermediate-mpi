Quick Reference
---------------

.. glossary::


   intracommunicator
      Foo

   intercommunicator
      Foo

   window
   memory window
   remote memory window
      Process-local memory allocated for remote memory access operations. It is of implementation-dependent type ``MPI_Win``.

   synchronization
      The necessary coordination of remote memory accesses. It can be *active* or *passive*.

   typemap
      Abstraction used to represent a datatypes in MPI. It is an associative
      array (map) with datatypes, as understood by MPI, as *keys* and
      displacements, in bytes, as *values*. The displacements are computed
      relative to the buffer the datatype describes.

      .. math::

         \textrm{Typemap} = \{ \textrm{Datatype}_{0}: \textrm{Displacement}_{0}, \ldots, \textrm{Datatype}_{n-1}: \textrm{Displacement}_{n-1} \}

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
