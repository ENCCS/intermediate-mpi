Non-blocking collective communication
=====================================

.. questions::

   - Is the synchronization of collective communications avoidable?

.. objectives::

   - Understand that a non-blocking barrier is useful


Introduction
------------

Just like for point-to-point messages, applications that use
non-blocking collectives can be more efficient than blocking
ones. This is because the latency of communication can overlap with
unrelated computation.


Non-blocking barrier synchronization
------------------------------------

At first glance, this seems like a nonsense. However if a barrier is
needed, then it can be quite useful to overlap work with the
synchronization. Use cases are rare, but include highly unstructured
work described by variable numbers of messages sent between ranks, or
very latency-sensitive applications. Once all messages have been sent,




It is necessary to use blocking barrier only when communicating
through a side channel, like a file or a socket.

See also
--------


* TODO
* TODO



.. keypoints::

   - TODO
   - point 2
   - ...
