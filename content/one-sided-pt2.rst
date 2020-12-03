.. _one-sided-2:


One-sided communication: synchronization
========================================

.. questions::

   - What are the pitfalls of RMA?
   - How can we make RMA safe and correct?

.. objectives::

   - Active synchronization: |term-MPI_Win_fence|, |term-MPI_Win_post|, |term-MPI_Win_start|, |term-MPI_Win_complete|, |term-MPI_Win_wait|
   - Passive synchronization: |term-MPI_Win_lock|, |term-MPI_win_unlock|


.. figure:: img/send-recv_step2.svg
   :align: center

   Two-sided communication between two sloths. Both of them are **active**
   participants in the communication: the |term-MPI_Send| has to be matched by
   an |term-MPI_Recv|.


Epochs
------

Active synchronization
----------------------

Passive synchronization
-----------------------


See also
--------

* The lecture covering MPI RMA from EPCC is available
  `here <http://www.archer.ac.uk/training/course-material/2020/01/advMPI-imperial/Slides/L08-Advanced%20RMA.pdf>`_
* Chapters 3 and 4 of the **Using Advanced MPI** by William Gropp *et al.* :cite:`Gropp2014-dz`



.. keypoints::

   - RMA epochs and synchronization.
   - The difference between *active* and *passive* synchronization.
   - How and when to use different synchronization models.
