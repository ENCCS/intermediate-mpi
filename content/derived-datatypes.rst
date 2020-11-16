Derived datatypes
=================

.. questions::

   - How can you reduce the number of messages sent and received?
   - How can you use your own derived datatypes as content of messages?

.. objectives::

   - Understand how MPI handles datatypes and the :term:`typemap` concept.
   - Learn to send and receive composite messages with |term-MPI_Pack| and |term-MPI_Unpack|
   - Learn how to represent your own derived datatypes as MPI messages with |term-MPI_Type_create_struct| and |term-MPI_Type_commit|
   - Learn how to represent homogeneous collections as MPI messages. |term-MPI_Type_contiguous|, |term-MPI_Type_vector|, |term-MPI_Type_indexed|


.. figure:: img/ENCCS.jpg
   :class: with-border

   This is the caption.


Topic introduction here

You really want to browse this page alongside the source of it, to see
how this is implemented.  See the links at the to right of the page.



Representation of datatypes in MPI
----------------------------------

- Typemaps
- Type signature
- Lower bounds, upper bounds, extents

:cite:`Gropp2014-qf`


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
