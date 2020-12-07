Using MPI and threads
=====================

.. questions::

   - TODO

.. objectives::

   - TODO


Why move past pure-MPI programs?
--------------------------------

MPI is an excellent tool for parallel execution of programs. A key
strength is that the programmer must explicitly move data to where it
is needed. That can make code easier to understand, albeit more work
to write. Since one writes code less often than the author *and
maintainers* read it, that is often desirable.

However, such approaches tend to perform poorly at scale. Computer
hardware has not grown much faster in the last 20 years, but instead
made many more potentially parallel execution units available. One can
hardly buy a single-core CPU any more, and HPC nodes with multiple CPU
sockets each containing scores of cores abound. MPI was designed in an
era where it was much more common to find a node with only a single
processor and a single core, and total counts were in the hundreds to
thousands. Such jobs are often *too small* to be permitted to run on
current high-end clusters.

Code that assumes one MPI process to a core has trouble scaling to
:math:`N` processes (eg. for N > 1000) for several reasons:

* collective communication cost tends to scale at least like
  :math:`\mathrm{log} N` - aggregating messages helps a lot but more
  processes as starting and ending points for messages simply must
  take more time

* data must be replicated to each process, which takes time that grows
  with the process count

* replicated data forces cores to share the memory bandwith, thus
  defeating the advantages of shared memory caches

MPI + threading
---------------
  
The MPI standard has been updated to accommodate the use of threads
within processes. Using this is optional, and presents numerous
advantages and disadvantages

Advantages of MPI + threading
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* possiblity for better scaling of communication costs

* either simpler and/or faster code that does not need to distribute
  as much data, because all threads in the process can share it
  already

* higher performance from using memory caches better

* reduced need to dedicate a rank solely to communication coordination
  in code using a manager-worker paradigm

* TODO

Disadvantages of MPI + threading
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* implicitly shared data can be harder to reason about correctly
  (eg. race conditions)

* code now has to be correct MPI code *and* correct threaded code

* possibility of lower performance from cache contention

* more code complexity

* might be merely shifting bottlenecks from one place to another
  (eg. opening and closing OpenMP thread regions)

* needs higher quality MPI implementations

* TODO

Threading library options
-------------------------

`OpenMP <https://www.openmp.org/>`_ is the open standard for HPC
threading, and is widely used with many quality implementations. It is
possible to use raw ``pthreads``, and you will find MPI examples using
them, but this is much less productive in programmer time and made
more sense when OpenMP was less mature. In most HPC cases, OpenMP is
implemented using ``pthreads``.

This workshop will use simple OpenMP for illustrative purposes.

MPI support for threading
-------------------------

Since version 2.0, MPI can be initialized in up to four different ways. The former
approach using ``MPI_Init`` still works, but applications that wish to use
threading should use |term-MPI_Init_thread|.

Call signature::

  int MPI_Init_thread(int *argc, char ***argv, int required, int *provided)

.. note::

   The ``argc`` and ``argv`` may be ``NULL`` (and generally should
   be). ``required`` describes the level of threading support that is
   requested, and the value returned in ``*provided`` describes the
   level that the MPI runtime was able to provide. If this is not the
   level required, the program should inform the user and either use
   threading only at the level provided, or ``MPI_Finalize`` and
   e.g. ``exit()``.


The following threading levels are generally supported:

* ``MPI_THREAD_SINGLE`` - rank is not allowed to use threads,
  which is basically equivalent to calling ``MPI_Init``.

  .. figure:: img/MPI_THREAD_SINGLE.svg
     :align: center
     :class: with-border

     With ``MPI_THREAD_SINGLE``, the rank may use MPI freely
     and will not use threads.


* ``MPI_THREAD_FUNNELED`` - rank can be multi-threaded but only
  the main thread may call MPI functions. Ideal for fork-join
  parallelism such as used in ``#pragma omp parallel``, where *all*
  MPI calls are outside the OpenMP regions.

  .. figure:: img/MPI_THREAD_FUNNELED.svg
     :align: center
     :class: with-border

     With ``MPI_THREAD_FUNNELED``, the rank can use MPI from
     only the main thread.


* ``MPI_THREAD_SERIALIZED`` - rank can be multi-threaded but
  only one thread at a time may call MPI functions. The rank
  must ensure that MPI is used in a thread-safe way. One approach is
  to enssure that MPI usage is *mutually excluded* by all the threads,
  eg. with a *mutex*.


  .. figure:: img/MPI_THREAD_SERIALIZED.svg
     :align: center
     :class: with-border

     With ``MPI_THREAD_SERIALIZED``, the rank can use MPI from
     any thread so long as it ensures the threads synchronize such
     that no thread calls MPI while another thread is doing so.


* ``MPI_THREAD_MULTIPLE`` - rank can be multi-threaded and any
  thread may call MPI functions. The MPI library ensures that this
  access is safe across threads. Note that this makes all MPI
  operations less efficient, even if only one thread makes MPI calls,
  so should be used only where necessary.

  .. figure:: img/MPI_THREAD_MULTIPLE.svg
     :align: center
     :class: with-border

     With ``MPI_THREAD_MULTIPLE``, the rank can use MPI from
     any thread. The MPI library ensures the necessary synchronization


Note that different MPI ranks may make different requirements for MPI
threading. This can be efficient for applications using manager-worker
paradigms where the workers have simpler communication patterns.

For applications where it is possible to implement using
``MPI_THREAD_SERIALIZED`` approach, it will generally outperform the
same application naively implemented and using
``MPI_THREAD_MULTIPLE``, because the latter will need to use more
synchronization.



See also
--------


* TODO
* TODO



.. keypoints::

   - TODO
   - point 2
   - ...
