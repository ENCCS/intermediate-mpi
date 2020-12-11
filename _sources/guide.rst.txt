Instructor's guide
------------------

Learning outcomes
=================

- Communicators, groups, derived datatypes
- One-sided communication
- Collective communication, blocking and non-blocking
- MPI and threads

Tips
====

- Append ``?plain=1`` to collapse the sidebar while presenting.
  Suggestion from `Richard Darst <https://github.com/coderefinery/sphinx-lesson/issues/53#issuecomment-741676048>`_.

Timing
======

This training material covers intermediate-level aspects of MPI programming.


First iteration: 2020-12-08/11
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

First iteration of this workshop was given as 4 x (almost) 4 hours, that is 4 half days.

We had two main 30-minutes lectures each day. Each lecture included type-alongs
and was followed by ample time for questions and live-coding demos.  Each day
was concluded with exercises and a wrap-up.

**Day 1 - Tuesday 8 December 2020 – Communicators, groups, derived datatypes**

  .. csv-table::
     :widths: auto
     :align: center
     :delim: ;

      9:00 -  9:10 ; Welcome and introduction to the training course
      9:10 - 10:30 ; **Using communicators in applications and libraries**
     10:30 - 10:45 ; Break
     10:45 - 11:25 ; **Handling derived datatypes**
     11:25 - 12:20 ; Exercises
     12:20 - 12:30 ; Wrap-up


**Day 2 - Wednesday 9 December 2020 - Collective communication (including nonblocking)**

  .. csv-table::
     :widths: auto
     :align: center
     :delim: ;

      9:00 -  9:10 ; What did we cover yesterday?
      9:10 - 09:45 ; **Simple collective communication**
      9:45 - 09:50 ; Break
      9:50 - 10:25 ; **Scatter and gather**
     10:30 - 10:35 ; Break
     10:35 - 11:10 : **Generalized forms of gather**
     11:10 - 11:20 ; Break
     11:20 - 11:40 ; **Non-blocking point-to-point communication**
     11:40 - 11:45 ; Break
     11:45 - 12:20 ; **Non-blocking collective communication**
     12:20 - 12:30 ; Wrap-up


**Day 3 - Thursday 10 December 2020 – One-sided communication**

  .. csv-table::
     :widths: auto
     :align: center
     :delim: ;

      9:00 -  9:10 ; What did we cover yesterday?
      9:10 - 10:30 ; **The whys and hows of remote memory access in MPI**
     10:30 - 10:45 ; Break
     10:45 - 11:25 ; **RMA and synchronization**
     11:25 - 12:20 ; Exercises
     12:20 - 12:30 ; Wrap-up


**Day 4 - Friday 11 December 2020 - MPI and threads**

  .. csv-table::
     :widths: auto
     :align: center
     :delim: ;

      9:00 -  9:10 ; What did we cover yesterday?
      9:10 -  9:40 ; **Why use MPI threading?**
      9:40 -  9:50 ; Break
      9:50 - 10:50 ; **How does MPI support threading?**
     10:50 - 11:00 ; Break
     11:00 - 11:30 ; **Using fork-join parallelism with MPI**
     11:30 - 11:40 ; Break
     11:40 - 12:10 ; **Using tasking with MPI**
     12:10 - 12:20 ; **Tips for hybrid MPI+OpenMP**
     12:20 - 12:30 ; Wrap-up
