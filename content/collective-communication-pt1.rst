Collective communication 1
==========================

.. questions::

   - How can all ranks of my program collaborate with messages?
   - How does collective messaging diff from point-to-point?

.. objectives::

   - Know the different kinds of collective message operations
   - Understand the terminology used in MPI about collective messages


Introduction
------------

Parallel programs often need to collaborate:

* To ensure that all ranks have reached a certain point (barrier)
* To share data with all ranks (broadcast)
* To compute based on data from all ranks (reduce)
* To rearrange data across ranks for subsequent computation (scatter, gather)

Barrier
-------

An ``MPI_Barrier`` call ensures that all ranks arrive at the call before
any of them proceeds past it.


`Man page <https://www.open-mpi.org/doc/v4.0/man3/MPI_Barrier.3.php>`_ for MPI_Barrier.

This is a section
-----------------

This is text.

A code block with preceeding paragraph::

  import multiprocessing

* A bullet list

* Bullet list

  * Sub-list::

      code block (note indention)

  .. note::

     directive within a list (note indention)


.. figure:: img/ENCCS.jpg
   :class: with-border

   This is the caption.

 
Exercise: the general topic
---------------------------

Exercises get their own section, so that they can be linked and found
in the table of contents.

.. challenge:: 1.1 Exercise title

   1. Notice the exercise set has both an ID and
      number ``SampleLesson-1`` and description of what it contains.

.. solution::

   * Solution here.


.. challenge:: 1.2 Create a lesson

   2. Similarly, each exercise has a quick description title ``Create
      a lesson`` in bold.  These titles are useful so that helpers
      (and learners...) can quickly understand what the point is.

.. solution::

   * Solution to that one.



Another section
---------------

.. instructor-note::

   This is an instructor note.  It may be hidden or put to the sidebar
   in a later style.  You should use it for things that the instructor
   should see while teaching, but should be de-emphasized for the
   learners.

A subsection
~~~~~~~~~~~~

.. figure:: img/sample-image.png

   Figure caption here.


.. figure:: img/sample-image.png
   :class: with-border

   Figure caption here, which explains the content in text so that
   it's accessible to screen readers.



See also
--------

* Upstream information
* Another course



.. keypoints::

   - What the learner should take away
   - point 2
   - ...
