INTERMEDIATE MPI
================

The Message Passing Interface (MPI) is the de facto standard for
distributed memory parallelism in high performance computing
(HPC). MPI is the dominant programming model for modern day
supercomputers and will continue to be critical in enabling
researchers to scale up their HPC workloads to forthcoming
pre-exascale and exascale systems.

This training material targets programmers who already have experience
with basic MPI and are ready to take the next step to more advanced
usage. Topics covered include communicators and groups, derived
datatypes, one-sided communication, collective communication and
hybrid MPI-threading approaches. :ref:`See below <learner-personas>`
for recommended prerequisite knowledge.


.. prereq::

   Before attending this workshop, please make sure that you have access
   to a computer with a C compiler and an MPI library installed. If you
   have access to a supercomputer (e.g. a `SNIC system <https://supr.snic.se/>`_)
   with a compute allocation you can use that during the workshop. Any questions
   on how to use a particular HPC resource should be directed to the appropriate
   support desk.  
   You can also use your own computer for this workshop, provided that it has
   compilers and an MPI library installed. If you do not already have these
   installed, we recommend that you set up an isolated software environment
   using ``conda``. For Windows computers we recommend to use the Windows
   Subsystem for Linux (WSL). Detailed instructions can be found 
   on the :doc:`setup` page.

.. toctree::
   :hidden:
   :maxdepth: 1

   setup

.. toctree::
   :hidden:
   :maxdepth: 1
   :caption: The lesson

   communicators-groups
   derived-datatypes
   collective-communication-pt1
   collective-communication-pt2
   collective-communication-pt3
   non-blocking-communication-pt1
   non-blocking-communication-pt2
   one-sided-pt1
   one-sided-pt2
   mpi-and-threads-pt1
   mpi-and-threads-pt2


.. csv-table::
   :widths: auto
   :align: left
   :delim: ;

   30 min ; :doc:`communicators-groups`
   30 min ; :doc:`derived-datatypes`
   35 min ; :doc:`collective-communication-pt1`
   35 min ; :doc:`collective-communication-pt2`
   35 min ; :doc:`collective-communication-pt3`
   60 min ; :doc:`non-blocking-communication-pt1`
   30 min ; :doc:`non-blocking-communication-pt2`
   60 min ; :doc:`one-sided-pt1`
   45 min ; :doc:`one-sided-pt2`
   60 min ; :doc:`mpi-and-threads-pt1`
   30 min ; :doc:`mpi-and-threads-pt2`

.. toctree::
   :maxdepth: 1
   :caption: Reference

   quick-reference
   zbibliography
   guide



.. _learner-personas:

Who is the course for?
----------------------

This course is for students, researchers, engineers and programmers
who already know the basics of MPI and want to learn more advanced MPI
topics. To derive benefit from this material you should have attended
introductory MPI training and preferably used basic MPI functionality
in some code projects.  Specifically, this lesson assumes that
participants have some prior experience with or knowledge of the
following topics (but no expertise is required):

 - General concepts: distributed memory parallelism, MPI process model
 - Communicators
 - Point-to-point communication
 - Non-blocking point-to-point communication
 - MPI datatypes

These pre-requisites are taught in courses such as `PDC's Introduction to MPI
<https://pdc-support.github.io/introduction-to-mpi/>`_  and the SNIC course `An
introduction to parallel programming using Message Passing with MPI
<http://www.lunarc.lu.se/training/an-introduction-to-parallel-programming-using-message-passing-with-mpi-1-4-december-2020/>`_.
 

About the course
----------------

This lesson material is developed by the `EuroCC National Competence
Center Sweden (ENCCS) <https://enccs.se/>`_ and taught in ENCCS
workshops. It is aimed at researchers and developers who already know
the basics of MPI. Each lesson episode has clearly defined learning
objectives and includes multiple exercises along with solutions, and
is therefore also useful for self-learning.
The lesson material is licensed under `CC-BY-4.0
<https://creativecommons.org/licenses/by/4.0/>`_ and can be reused in any form
(with appropriate credit) in other courses and workshops.
Instructors who wish to teach this lesson can refer to the :doc:`guide` for
practical advice.


Graphical and text conventions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

We adopt a few conventions which help organize the material.

Function signatures
   These are shown in a text block marked with a wrench emoji:

   .. signature:: ``MPI_Win_unlock``

      .. code-block:: c

         int MPI_Win_unlock(int rank,
                            MPI_Win win)

   The signature can be hidden by clicking the toggle.

Function parameters
   The description of the function parameters will appear in a separate text
   box. It will be marked with a laptop emoji:

   .. parameters::

      ``rank``
          The rank whose memory window should be unlocked.
      ``win``
          The window object.

   The description is hidden and will be shown by clicking the toggle.



See also
--------

There are many free online resources whose contents overlap with those covered
in this lesson.
Here is a non-comprehensive list:

- The `EPCC <https://www.epcc.ed.ac.uk/>`_ materials on `basic and intermediate
  MPI <https://github.com/EPCCed/archer2-MPI-2020-05-14>`_ and `advanced topics
  <http://www.archer.ac.uk/training/course-material/2020/01/advMPI-imperial/index.php>`_
- The freely available book `Parallel Programming for Science Engineering
  <https://pages.tacc.utexas.edu/~eijkhout/pcse/html/index.html>`_ by Viktor
  Eijkhout.
- The `MPI Standard <https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report/mpi31-report.htm>`_. It is very dry, technical material.


You can also consult the following books:

- **Parallel Programming with MPI** by Peter Pacheco.
- **Using MPI** by William Gropp, Ewing Lusk, and Anthony Skjellum.
- **Using Advanced MPI** by William Gropp, Torsten Hoefler, Rajeev Thakur, and Ewing Lusk.


Credits
-------

The lesson file structure and browsing layout is inspired by and derived from
`work <https://github.com/coderefinery/sphinx-lesson>`_ by `CodeRefinery
<https://coderefinery.org/>`_ licensed under the `MIT license
<http://opensource.org/licenses/mit-license.html>`_. We have copied and adapted
most of their license text.

Instructional Material
^^^^^^^^^^^^^^^^^^^^^^

All ENCCS instructional material is made available under the `Creative Commons
Attribution license (CC-BY-4.0)
<https://creativecommons.org/licenses/by/4.0/>`_. The following is a
human-readable summary of (and not a substitute for) the `full legal text of the
CC-BY-4.0 license <https://creativecommons.org/licenses/by/4.0/legalcode>`_.
You are free:

- to **share** - copy and redistribute the material in any medium or format
- to **adapt** - remix, transform, and build upon the material for any purpose,
  even commercially.

The licensor cannot revoke these freedoms as long as you follow these license terms:

- **Attribution** - You must give appropriate credit (mentioning that your work
  is derived from work that is Copyright (c) ENCCS and, where practical, linking
  to `<https://enccs.se>`_), provide a `link to the license
  <https://creativecommons.org/licenses/by/4.0/>`_, and indicate if changes were
  made. You may do so in any reasonable manner, but not in any way that suggests
  the licensor endorses you or your use.
- **No additional restrictions** - You may not apply legal terms or
  technological measures that legally restrict others from doing anything the
  license permits. With the understanding that:

  - You do not have to comply with the license for elements of the material in
    the public domain or where your use is permitted by an applicable exception
    or limitation.
  - No warranties are given. The license may not give you all of the permissions
    necessary for your intended use. For example, other rights such as
    publicity, privacy, or moral rights may limit how you use the material.
  
Software
^^^^^^^^

Except where otherwise noted, the example programs and other software provided
by ENCCS are made available under the `OSI <http://opensource.org/>`_-approved
`MIT license <http://opensource.org/licenses/mit-license.html>`_.
