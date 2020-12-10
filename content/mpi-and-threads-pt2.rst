MPI and threads in practice
===========================

.. questions::

   - TODO

.. objectives::

   - TODO


.. figure:: img/fork-join-parallelism.svg
   :align: center

   OpenMP is particularly suited for fork-join parallelism. Beware
   that each parallel region requires synchronization between threads
   and the speed-up depends critically on the time spent in the
   single-threaded regions!


Topic introduction here

You really want to browse this page alongside the source of it, to see
how this is implemented.  See the links at the to right of the page.


See also
--------

* `Hybrid MPI-OpenMP best practices <http://www.intertwine-project.eu/sites/default/files/images/INTERTWinE_Best_Practice_Guide_MPI%2BOpenMP_1.2.pdf>`_

.. keypoints::

   - What the learner should take away
   - point 2
   - ...
