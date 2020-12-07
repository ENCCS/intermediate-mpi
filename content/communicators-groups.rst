.. _comms-groups:


Communicators and groups
========================

.. questions::

   - How can we write safe parallel libraries?

.. objectives::

   - Learn about tagging of messages and why it is an unsafe mechanism to distinguish library and host messages.
   - Learn the difference between :term:`intracommunicator` and :term:`intercommunicator`.
   - Learn how to create communicators by splitting with |term-MPI_Comm_split|.



.. todo::

   Possible example/exercise: computing :math:`\pi` with Monte Carlo integration. The point being that we delegate one process to handle the PRNG. See :cite:`Gropp2014-qf`.



See also
--------

* Chapters 3, 4, and 6 of the **Using MPI** book by William Gropp *et al.* show examples of using the functions described in this episode. :cite:`Gropp2014-qf`
* Chapter 7 of the **Parallel Programming with MPI** book by Peter Pacheco. :cite:`Pacheco1997-qq`

.. keypoints::

   - You can use tags to differentiate the source of messages, but this approach is neither scalable nor safe.
   - You can create new communicators by splitting or grouping.
