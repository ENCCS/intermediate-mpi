.. _derived-datatypes:


Derived datatypes
=================

.. questions::

   - How can you reduce the number of messages sent and received?
   - How can you use your own derived datatypes as content of messages?

.. objectives::

   - Understand how MPI handles datatypes and the :term:`typemap` concept.
   - Learn to send and receive composite messages with |term-MPI_Pack| and |term-MPI_Unpack|
   - Learn how to represent homogeneous collections as MPI messages. |term-MPI_Type_contiguous|, |term-MPI_Type_vector|, |term-MPI_Type_indexed|
   - Learn how to represent your own derived datatypes as MPI messages with |term-MPI_Type_create_struct| and |term-MPI_Type_commit|
   -  MAYBE: Learn how to define combination operations on your datatypes: |term-MPI_Op_create| and |term-MPI_Op_free|


Topic introduction here

You really want to browse this page alongside the source of it, to see
how this is implemented.  See the links at the to right of the page.



Representation of datatypes in MPI
----------------------------------

- ``MPI_Datatype`` and typemaps
- Type signature
- Lower bounds, upper bounds, extents
- Difference between *size* and *extent* of a datatype.
- Introduce |term-MPI_Type_get_extent| and |term-MPI_Type_size|



.. code-block:: c

   struct simple {
    int an_integer;
    char a_char;
   };

.. figure:: img/sample-image.png
   :class: with-border

   The relation between size and extent of a derived data type for the case of the ``simple`` datatype.

.. todo::

   - Draw diagram showing how to calculate the extent from a typemap.
   - Type-along showing how to get extent and size of basis datatypes.


Datatype constructors in MPI
----------------------------

- Contiguous types: |term-MPI_Type_contiguous|
- Extent-strided types: |term-MPI_Type_vector|
- Byte-strided types: |term-MPI_Type_create_hvector|
- Extent-indexed types: |term-MPI_Type_indexed|
- Byte-strided types: |term-MPI_Type_create_hindexed|
- General types: |term-MPI_Type_create_struct|
- Register and unregister your types: |term-MPI_Type_commit|, |term-MPI_Type_free|

.. figure:: img/sample-image.png
   :class: with-border

   The lifecycle of user-defined datatypes in MPI.

.. todo::

   - Draw diagram showing how new types are created and used: any of the type constuctors, |term-MPI_Type_commit|, use, |term-MPI_Type_free|
   - Type-along showing how to declare and use a contiguous type.
   - Type-along showing the use and meaning of extent and count. See 5.1.3 in :cite:`Gropp2014-qf`


.. todo::

   - pack/unpack send your address. Gotchas: strings need to be statically sized and the size sent separately!


See also
--------

* The lecture covering MPI datatypes from EPCC is available on `GitHub <https://github.com/EPCCed/archer2-MPI-2020-05-14/blob/master/slides/L10-derivedtypes.pdf>`_
* Chapter 5 of the **Using MPI** book by William Gropp *et al.* :cite:`Gropp2014-qf`
* Chapter 6 of the **Parallel Programming with MPI** book by Peter Pacheco. :cite:`Pacheco1997-qq`


.. keypoints::

   - A low-level representation as typemap can be associated with any derived data structure.
   - Typemaps are essential to enable MPI communication of complex data types.
