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
