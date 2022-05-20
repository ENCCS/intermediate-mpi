.. _derived-datatypes-pt1:


Derived datatypes: pack and unpack
==================================

.. questions::

   - How can you reduce the number of messages sent and received?

.. objectives::

   - Learn how to pack heterogeneous data into a single message.


MPI supports many of the basic datatypes recognized by the C and Fortran standards.
However, often one needs to represent data that requires more complex programming structures than just the fundamental datatypes.


.. csv-table:: Basic datatypes in MPI and in the C standard. For a comprehensive
               explanation of the types defined in the C language, you can
               consult `this reference
               <https://en.cppreference.com/w/c/language/type>`_.
   :widths: auto
   :align: center
   :header-rows: 1
   :delim: ;

   MPI ; C
   ``MPI_CHAR`` ; ``signed char``
   ``MPI_FLOAT`` ; ``float``
   ``MPI_DOUBLE`` ; ``double``
   ``MPI_LONG_DOUBLE`` ; ``long double``
   ``MPI_WCHAR`` ; ``wchar_t``
   ``MPI_SHORT`` ; ``short``
   ``MPI_INT`` ; ``int``
   ``MPI_LONG`` ; ``long``
   ``MPI_LONG_LONG_INT`` ; ``long long``
   ``MPI_SIGNED_CHAR`` ; ``signed char``
   ``MPI_UNSIGNED_CHAR`` ; ``unsigned char``
   ``MPI_UNSIGNED_SHORT`` ; ``unsigned short``
   ``MPI_UNSIGNED`` ; ``unsigned int``
   ``MPI_UNSIGNED_LONG`` ; ``unsigned long``
   ``MPI_UNSIGNED_LONG_LONG`` ; ``unsigned long long``
   ``MPI_C_COMPLEX`` ; ``float _Complex``
   ``MPI_C_DOUBLE_COMPLEX`` ; ``double _Complex``
   ``MPI_C_LONG_DOUBLE_COMPLEX`` ; ``long double _Complex``
   ``MPI_PACKED`` ;
   ``MPI_BYTE`` ;

The MPI standard defines functions to extend the datatypes that can be used in MPI messages. In this episode, we will discuss how to collect heterogeneous data into a single MPI message, leaving the definition of your own types to next episode :ref:`derived-datatypes-pt2`.


Packing and unpacking
---------------------

MPI offers the possibility to pack and unpack data of known datatype into a
single contiguous memory buffer, *without* first having to define a
corresponding datatype.
This can be an extremely useful technique to reduce messaging traffic and could
help with the readability and portability of the code.
The resulting packed buffer will be of type ``MPI_PACKED`` and can contain any
sort of heterogeneous collection of basic datatypes recognized by MPI.


.. figure:: img/E01-pack_unpack.svg
   :align: center

   MPI allows the programmer to communicate heterogeneous collections into a
   single message, without defining a full-fledged custom datatype. The data is
   packed into a buffer of type ``MPI_PACKED``. On the receiving end, the buffer
   will be unpacked into its constituent components.


.. signature:: |term-MPI_Pack|

   Pack data in noncontiguous memory to a contiguous memory buffer.

   .. code-block:: c

      int MPI_Pack(const void *inbuf,
                   int incount,
                   MPI_Datatype datatype,
                   void *outbuf,
                   int outsize,
                   int *position,
                   MPI_Comm comm)


.. figure:: img/E01-pack.svg
   :align: center

   The relation of ``inbuf``, ``outbuf``, and ``position`` when calling
   ``MPI_Pack``.  In this figure, ``outbuf`` already holds some data (the red
   shaded area). The data in ``inbuf`` is copied to ``outbuf`` starting at the
   address ``outbuf+*position``.  When the function returns, the ``position``
   parameter will have been updated to refer to the *first* position in ``outbuf``
   following the data copied by this call.


.. parameters::

   ``inbuf``
     The input buffer, *i.e.* the data to be packed into contigous memory.
   ``incount``
     Number of input data items.
   ``datatype``
     The datatype of each item to be packed.
   ``outbuf``
     Starting address of the output buffer.
   ``outsize``
     The size, in bytes, of the output buffer.
   ``position``
     This is an input/output parameter that describes locations within
     ``outbuf``. The data at ``inbuf`` will be copied to ``outbuf + *position``.
     After the function returns, the value ``*position`` indicates the first
     position in ``outbuf`` that follows the data just copied.
     This is useful to pass as ``position`` to the next call to ``MPI_Pack``.
   ``comm``
     The communicator.

.. signature:: |term-MPI_Unpack|

   Unpack a contiguous memory buffer into noncontiguous memory locations.

   .. code-block:: c

      int MPI_Unpack(const void *inbuf,
                     int insize,
                     int *position,
                     void *outbuf,
                     int outcount,
                     MPI_Datatype datatype,
                     MPI_Comm comm)


.. figure:: img/E01-unpack.svg
   :align: center

   The relation of ``inbuf``, ``outbuf``, and ``position`` when calling
   ``MPI_Unpack``.  In this figure, ``inbuf`` holds some data. The data
   in ``inbuf`` is copied to ``outbuf`` starting at the address given with
   ``position``.  When the function returns, the ``position`` parameter will
   have been updated to the *first* position in ``inbuf`` following the just
   copied data.


.. parameters::

   ``inbuf``
     The input buffer, *i.e.* the data to be unpacked.
   ``insize``
     The size, in bytes, of the input buffer.
   ``position``
     This is an input/output parameter that describes locations within
     ``inbuf``. The data at ``inbuf + *position`` will be copied to ``outbuf``.
     After the function returns, the value ``*position`` indicates the first
     position in ``inbuf`` that follows the data just copied.
     This is useful to pass as ``position`` to the next call to ``MPI_Unpack``.
   ``outbuf``
     Starting address of the output buffer.
   ``outcount``
     Number of output data items.
   ``datatype``
     The datatype of each item to be unpacked.
   ``comm``
     The communicator.


.. challenge:: Message passing Pokémons

   In the Pokémon trading card game, opponents face each in duels using their
   pokémons. The game is played in turns and at each turn a player can attack.
   We have to send:

   - The attacking pokémon's name: a ``char`` array.
   - How many life points it has: a ``double``.
   - The damage its attack will inflict: an ``int``.
   - A damage multiplier: a ``double``.

   .. tabs::

      .. tab:: Pack and unpack

         You can find a scaffold for the code in the
         ``content/code/day-1/05_pokemon-pack-unpack`` folder. You will have to
         complete the source code to compile and run correctly: follow the hints
         in the source file.  A working solution is in the ``solution``
         subfolder.

         #. Pack the data in the ``message`` buffer.
         #. Unpack the ``message`` buffer into its component data.

         Compile with::

           mpicc -g -Wall -std=c11 pokemon-pack-unpack.c -o pokemon-pack-unpack

         - Why are we hardcoding the length of the pokémon's name?
         - What is the purpose of the ``position`` variable? Print its value
           after each packing and unpacking. Do these values conform with your
           intuition?
         - Should packing and unpacking happen in the same order? What happens if not?
         - What happens when there is a mismatch of types between packing and unpacking?
         - We could have packed our data as ``char``, ``int``, ``double``, and
           ``double``. Is there a way to pack (unpack) the life points and the
           damage multiplier with one call to ``MPI_Pack`` (``MPI_Unpack``)?

      .. tab:: Bonus

         The ``message`` is a buffer of size ``BUFSIZ`` (defined in the standard
         header ``stdio.h``) We cannot always be sure this is the correct
         choice: the space might be plentiful, in which case we're wasting
         resource, or it might not be enough, in which case the program is not
         safe and likely not even portable!

         MPI offers the function |term-MPI_Pack_size| for this purpose. Look up its
         documentation and modify the source code such that the buffer is sized
         more appropriately.
         What could be problematic with the pack/unpack approach?

         A working solution is in the
         ``content/code/day-1/06_pokemon-pack-unpack-size/solution`` folder.

      .. tab:: Superbonus

         The length of the string holding the pokémon's name is hardcoded to a
         constant. How would you generalize this program?


See also
--------

* The lecture covering MPI datatypes from EPCC is available on `GitHub <https://github.com/EPCCed/archer2-MPI-2020-05-14/blob/master/slides/L10-derivedtypes.pdf>`_
* Chapter 5 of the **Using MPI** book by William Gropp *et al.* :cite:`Gropp2014-qf`
* Chapter 6 of the **Parallel Programming with MPI** book by Peter Pacheco. :cite:`Pacheco1997-qq`


.. keypoints::

   - You can reduce message traffic by packing (unpacking) heterogeneous data together.
   - Packing/unpacking are straightforward to use, but might lead to less
     readable programs.
