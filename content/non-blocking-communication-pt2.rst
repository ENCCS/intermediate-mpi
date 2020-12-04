Non-blocking collective communication
=====================================

.. questions::

   - Is the synchronization of collective communications avoidable?

.. objectives::

   - Understand that a non-blocking barrier is useful


Introduction
------------

Just like for point-to-point messages, applications that use
non-blocking collectives can be more efficient than blocking
ones. This is because the latency of communication can overlap with
unrelated computation.


Non-blocking barrier synchronization
------------------------------------

At first glance, this seems like a nonsense. However if a barrier is
needed, then it can be quite useful to overlap work with the
synchronization. Use cases are rare, but include highly unstructured
work described by variable numbers of messages sent between ranks, or
very latency-sensitive applications. Once all messages have been sent,




It is necessary to use blocking barrier only when communicating
through a side channel, like a file or a socket.

Non-blocking reduce
-------------------

TODO graphic and description of |term-MPI_Ireduce|


Code-along exercise: non-blocking ireduce during stencil workflow
-----------------------------------------------------------------

.. challenge:: 1.1 Observe a running total during a stencil workflow

   1. Download the :download:`source code
      <code/non-blocking-communication-ireduce.c>`. Open
      ``non-blocking-communication-ireduce.c`` and read through it. It
      is quite similar to that for the earlier non-blocking code-along
      exercise. Compile with::

        mpicc -g -Wall -std=c11 non-blocking-communication-ireduce.c -o non-blocking-communication-ireduce

   2. When you have the code compiling, try to run with::

        mpiexec -np 2 ./non-blocking-communication-ireduce

   4. Try to fix the code TODO

.. solution::

   * One correct approach is::

        TODO

   * There are other approaches that work correctly. Is yours better
     or worse than this one? Why?
   * Download a :download:`working solution <code/non-blocking-communication-ireduce-solution.c>`


See also
--------


* TODO
* TODO



.. keypoints::

   - TODO
   - point 2
   - ...
