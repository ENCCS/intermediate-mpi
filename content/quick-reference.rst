Quick Reference
---------------

.. glossary::

   ``MPI_Comm_split``
      Function to split an existing communicator.

      .. code-block:: c

         int MPI_Comm_split(MPI_Comm comm,
                            int color,
                            int key,
                            MPI_Comm *newcomm)

      |MPI_Comm_split-implementors_docs|
