.. _comms-groups:


Communicators and groups
========================

.. questions::

   - How can we write safe parallel libraries?

.. objectives::

   - Learn about tagging of messages and why it is an unsafe mechanism to distinguish library and host messages.
   - Learn the difference between :term:`intracommunicator` and :term:`intercommunicator`.
   - Learn how to create communicators by splitting with |term-MPI_Comm_split|.


Topic introduction here

You really want to browse this page alongside the source of it, to see
how this is implemented.  See the links at the to right of the page.


.. todo::

   Possible example/exercise: computing :math:`\pi` with Monte Carlo integration. The point being that we delegate one process to handle the PRNG. See :cite:`Gropp2014-qf`.

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

* Chapters 3, 4, and 6 of the **Using MPI** book by William Gropp *et al.* show examples of using the functions described in this episode. :cite:`Gropp2014-qf`
* Chapter 7 of the **Parallel Programming with MPI** book by Peter Pacheco. :cite:`Pacheco1997-qq`

.. keypoints::

   - You can use tags to differentiate the source of messages, but this approach is neither scalable nor safe.
   - You can create new communicators by splitting or grouping.
