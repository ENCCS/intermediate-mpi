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


The use of software libraries allows programmers to develop new software without
having to reinvent the wheel every time one is needed.
Software components, if properly packaged and documented, can be easily reused
and combined to fit the programmers purposes.
How can we write high quality libraries that can efficiently exploit parallelism
in the message passing model?

Let us have a look at the basic point-to-point communication routines
``MPI_Send`` and ``MPI_Recv``.

.. figure:: img/E02-send-recv_step2.svg
   :align: center

   Point-to-point communication between two sloths. The tag of the message can
   be used to match messages between sending and receiving partners.



.. signature:: ``MPI_Send``

   .. code-block:: c

      int MPI_Send(const void *buf,
                   int count,
                   MPI_Datatype datatype,
                   int dest,
                   int tag,
                   MPI_Comm comm)

.. signature:: ``MPI_Recv``

   .. code-block:: c

      int MPI_Recv(void *buf,
                   int count,
                   MPI_Datatype datatype,
                   int source,
                   int tag,
                   MPI_Comm comm,
                   MPI_Status *status)


Both accept a ``tag`` parameter, used to match messages sent and received.  As a
library author, you might decide to reserve any range of integers for exclusive
use as tags for messages originating from your code. This is however far from an
optimal solution:

1. You are imposing a restrictive design onto your potential users. This is a
   choice that is not intrinsic to the problem domain and usually suggests a bad
   design.
2. The design is not *extensible*. What if you run out of tags and need to add a
   new one to the reserved list? You will break your API or, worse, will
   interfere with existing tagging in client code.
3. You library is not, most likely, the only one used. How can you guarantee
   that your choice of reserved tags is unique?

Clearly, using tags to distinguish the origin of messages *does not scale* with
the number of components involved in a software project and will reduce the
extensibility and maintainability of the codebase.

Note that ``MPI_Send`` and ``MPI_Recv`` also take a communicator as parameter
and indeed the use of communicators is the solution offered by the MPI standard
for the problems faced by library authors.
Even if you are not writing parallel libraries, it is a good idea to get
acquainted with the concepts of **communicators** and **groups**.  Communicators
come in two flavors:

1. **Intracommunicators**. Essentially a collection of processes that can
   interact through point-to-point *and* collective message passing routines.
2. **Intercommunicators**. These are collection of processes in *disjoint*
   intracommunicators that can interact through message passing.

Intracommunicators are the most commonly occuring flavor. We will only deal with
intracommunicators in this lesson and, following general practice, we will
simply call them communicators from now on.
A communicator consists of:

- A **group**, *i.e.* an ordered collection of processes. Each process in the
  group is assigned a **rank**, a non-negative integer number. The rank uniquely
  identifies each process in the group.
- A **context**, *i.e.* a system-defined object that identifies each
  communicator uniquely. Since the context is unique to the communicator, the
  same group can span *different* communicators, without causing issues.


.. typealong:: It's a wonderful ``MPI_COMM_WORLD``

   ``MPI_COMM_WORLD`` is the default communicator: it is spanned by the group of
   processes specified when launching your program::

     mpirun -np 2 program

   Let's get reacquainted with some functions with communicators as parameters.
   Probably the most basic ones are:

   - ``MPI_Comm_size``, to obtain the size of the group spanning the
     communicator.
   - ``MPI_Comm_rank``, to obtain the rank of the calling process in the group
     spanning the communicator.

   We cannot modify the context of a communicator directly, but we can get its
   group with the |term-MPI_Comm_group| function:

   .. signature:: |term-MPI_Comm_group|

      .. code-block:: c

         int MPI_Comm_group(MPI_Comm comm,
                            MPI_Group *group)

   A group has type ``MPI_Group``, it is good practice to clean up the memory
   used by such an object calling |term-MPI_Group_free|.

   .. signature:: |term-MPI_Comm_free|

      .. code-block:: c

         int MPI_Comm_free(MPI_Comm *comm)

   What can we do with groups? Quite a lot, it turns out! Processes in a group
   form a *set*. We can create new groups by:

   - explicitly *including* and *excluding* processes from an existing group.
   - performing set operations, such as intersection and difference, between
     groups.

   Exclusion and inclusion of processes are done with integer arrays of ranks,
   recall that the rank is the unique identifier of a process within a group.

   .. signature:: |term-MPI_Group_excl|

      .. code-block:: c

         int MPI_Group_excl(MPI_Group group,
                            int n,
                            const int ranks[],
                            MPI_Group *newgroup)

   Once we have a group, a call to |term-MPI_Comm_create| will handily give us a
   new communicator spanned by the processes in the group.

   .. signature:: |term-MPI_Comm_create|

      .. code-block:: c

         int MPI_Comm_create(MPI_Comm comm,
                             MPI_Group group,
                             MPI_Comm *newcomm)

   The new communicator is an object of ``MPI_Comm`` type, which can be used in
   any context where you would have used ``MPI_COMM_WORLD``.  You can clean up
   such an object with |term-MPI_Comm_free|.

   Manipulation of groups can be a tedious affair. It is usually more convenient
   to create new communicators by splitting existing ones with
   |term-MPI_Comm_split|.

   .. signature:: |term-MPI_Comm_split|

      .. code-block:: c

         int MPI_Comm_split(MPI_Comm comm,
                            int color,
                            int key,
                            MPI_Comm *newcomm)

   .. parameters::

      ``comm``
        The existing communicator to split.

      ``color``
        The criterion by which to assign the calling process to the new communicator.

      ``key``
        The relative rank of the calling process in the group of the new communicator.

      ``newcomm``
        The new communicator. ``newcomm`` and ``comm`` will not overlap.


.. challenge:: Warm up your communicators and your groups

   Time for some practice! We will run with 4 processes, divide them evenly into two
   groups and create a new communicator out of them.

   Download the :download:`scaffold source code
   <code/comms-groups-divide-evenly.c>`.  Open it and read through it. Address
   the ``FIXME`` points appropriately. Compile with::

     mpicc -g -Wall -std=c11 comms-groups-divide-evenly.c -o comms-groups-divide-evenly

   Download a :download:`working solution <code/comms-groups-divide-evenly-solution.c>`


.. challenge:: Calculating :math:`\pi`

   The computation of high-dimensional integrals with Monte Carlo method can be
   quite efficient.  We will aim at a more modest target here: the calculation
   of :math:`\pi` by Monte Carlo sampling.
   Given a circle of radius 1, the ratio of randomly drawn points inside and
   outside the circle will converge to :math:`\frac{\pi}{4}`.
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
   #. Unless we meet the user-provided error threshold, checker processes will
      request a fresh batch of random data.

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

.. keypoints::

   - You can use tags to differentiate the source of messages, but this approach
     is neither scalable nor safe.
   - You can create new communicators by splitting or grouping.
