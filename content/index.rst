INTERMEDIATE MPI
================

TODO Intro



.. prereq::

   TODO What to prepare before the workshop?



.. toctree::
   :hidden:
   :maxdepth: 1
   :caption: The lesson

   communicators-groups
   derived-datatypes
   one-sided-pt1
   one-sided-pt2
   collective-communication-pt1
   collective-communication-pt2
   mpi-and-threads-pt1
   mpi-and-threads-pt2


.. csv-table::
   :widths: auto
   :delim: ;

   30 min ; :doc:`communicators-groups`
   30 min ; :doc:`derived-datatypes`
   30 min ; :doc:`one-sided-pt1`
   30 min ; :doc:`one-sided-pt2`
   30 min ; :doc:`collective-communication-pt1`
   30 min ; :doc:`collective-communication-pt2`
   30 min ; :doc:`mpi-and-threads-pt1`
   30 min ; :doc:`mpi-and-threads-pt2`


.. toctree::
   :maxdepth: 1
   :caption: Reference

   quick-reference
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
 - Collective communication
 - MPI datatypes

These pre-requisites are taught in courses such as `PDC's Introduction to MPI
<https://pdc-support.github.io/introduction-to-mpi/>`_  and the SNIC course `An
introduction to parallel programming using Message Passing with MPI
<http://www.lunarc.lu.se/training/an-introduction-to-parallel-programming-using-message-passing-with-mpi-1-4-december-2020/>`_.
 

About the course
----------------


TODO



See also
--------


TODO


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

- to **Share** - copy and redistribute the material in any medium or format
- to **Adapt** - remix, transform, and build upon the material for any purpose,
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
`MIT license <http://opensource.org/licenses/mit-license.html>`_::

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the “Software”), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
