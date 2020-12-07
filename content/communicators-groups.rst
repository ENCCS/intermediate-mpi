.. _comms-groups:


Communicators and groups
========================

.. questions::

   - How can we write safe parallel libraries?

.. objectives::

   - Learn about tagging of messages and why it is an unsafe mechanism to
     distinguish library and host messages.
   - Learn the difference between :term:`intracommunicator` and
     :term:`intercommunicator`.
   - Learn how to create new communicators.


.. typealong:: Something with intercommunicators

   sdfasdfoaj

|term-MPI_Comm_group|
|term-MPI_Group_excl|
|term-MPI_Comm_create|
|term-MPI_Group_free|
|term-MPI_Comm_free|


.. challenge:: Calculating :math:`pi`

   The computation of high-dimensional integrals with Monte Carlo method can be
   quite efficient.  We will aim at a more modest target here: the calculation
   of :math:`pi` by Monte Carlo sampling.  Given a circle of radius 1, the ratio
   of randomly drawn points inside and outside the circle will be
   :math:`\frac{\pi}{4}`.
   Rather than have every process invoke ``rand`` separately, we would like to
   reserve one single process for that purpose and use all the others to check
   whether these points are inside or outside the circle.
   To reduce communication traffic, this single process will fill and send a
   whole array of random numbers.

   1. Download the :download:`scaffold source code <code/pi-monte-carlo.c>`.
      Open it and read through it.
   #. Only one process will generate random data. Define a ``checkers_g`` group
      including all other processes which will be acting as checkers.
   #. Define a communicator for the checker processes.
   #. The ``rng`` process listens for requests and serves them by sending an
      array of random data. The scaffold defines ``REQUEST`` and ``REPLY`` tags.
   #. The ``checkers`` group goes through the random data and tallies the number
      of points inside and outside the circle.
   #. Unless the user-set error threshold is met, checker processes will request
      a fresh batch of random data.

   Compile with::

     mpicc -g -Wall -std=c11 pi-monte-carlo.c -o pi-monte-carlo

   Download a :download:`working solution <code/pi-monte-carlo-solution.c>`

See also
--------

* Chapters 3, 4, and 6 of the **Using MPI** book by William Gropp *et al.* show
  examples of using the functions described in this episode.
  :cite:`Gropp2014-qf`
* Chapter 7 of the **Parallel Programming with MPI** book by Peter Pacheco.
  :cite:`Pacheco1997-qq`
* Chapter 10 of the **Using Advanced MPI** by William Gropp *et al.*
  :cite:`Gropp2014-dz`

.. keypoints::

   - You can use tags to differentiate the source of messages, but this approach
     is neither scalable nor safe.
   - You can create new communicators by splitting or grouping.
