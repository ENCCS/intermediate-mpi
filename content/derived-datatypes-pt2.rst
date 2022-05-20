.. _derived-datatypes-pt2:


Derived datatypes: ``MPI_Datatype``
===================================

.. questions::

   - How can you use your own derived datatypes as content of messages?

.. objectives::

   - Understand how MPI handles datatypes.
   - Learn to send and receive messages using composite datatypes.
   - Learn how to represent homogeneous collections as MPI datatypes.
   - Learn how to represent your own derived datatypes as MPI datatypes.


The ability to define custom datatypes is one of the hallmarks of a modern
programming language, since it allows programmers to structure their code in a
way that enhances readability and maintainability.
How can this be done in MPI? Recall that MPI is a standard describing a library
to enable parallel programming in the message passing model.

In the C language, types are **primitive** constructs: they
are *defined* by the standard and *enforced* by the compiler.
The MPI types are instead **variants** in the ``MPI_Datatype`` enumeration: they
appear as the **same** type to the compiler.
This is a fundamental difference which influences the way custom datatypes are handled.

In the C language, you would declare a ``struct`` such as the following:


.. code-block:: c

   struct Pair {
    int first;
    char second;
   };

``Pair`` is a new type. From the compiler's point of view, it has status on par
with the fundamental datatypes introduced above. The C standard makes requirements on *how
to* represent this in memory and the compiler will generate machine code to
comply with it.

MPI does not know how to represent user-defined datatypes in memory by itself:

- How much memory does it need? Recall that MPI deals with **groups of
  processes**. For portability, you can *never* assume that two processes share
  the same architecture!
- How are the components of ``Pair`` laid out in memory? Are they always
  contiguous? Or are they padded?

The programmer needs to provide this low-level information, such that the MPI
runtime can send and receive custom  datatypes as messages over a heterogeneous
network of processes.


Representation of datatypes in MPI
----------------------------------

The representation of datatypes in MPI uses few low-level concepts.
The **type signature** of a custom datatypes is the list of its basic datatypes:

.. math::
   :label: eq:typesig

   \textrm{Type signature}[\texttt{T}] = [ \texttt{Datatype}_{0}, \ldots, \texttt{Datatype}_{n-1} ]

The **typemap** is the associative array (map) with datatypes, as understood by MPI, as
*keys* and displacements, in bytes, as *values*.


.. math::
   :label: eq:typemap

   \textrm{Typemap}[\texttt{T}] = \{ \texttt{Datatype}_{0}: \textrm{Displacement}_{0}, \ldots, \texttt{Datatype}_{n-1}: \textrm{Displacement}_{n-1} \}


The displacements are *relative* to the buffer the datatype describes.

Assuming that an ``int`` takes 4 bytes of memory, the typemap for our ``Pair``
datatype would be: :math:`\textrm{Typemap}[\texttt{Pair}] = \{ \texttt{int}: 0,
\texttt{char}: 4\}`. Note again that the displacements are *relative*.

.. figure:: img/E01-displacements.svg
   :align: center

   Depiction of the typemap for the ``Pair`` custom type. The displacements are
   always relative.


Knowledge of typemap and type signature is not enough for a full description of
the type to the MPI runtime: the underlying programming language might mandate
architecture-specific :term:`alignment` of the basic datatypes. The data
structure would then be laid out in memory incoherently with the displacements
in its typemap.
We need a few more concepts. Given a typemap :math:`m` we can define:

Lower bound
  The first byte occupied by the datatype.

  .. math::
     :label: eq:lowerbound

     \textrm{LB}[m] = \min_{j}[\textrm{Displacement}_{j}]

Upper bound
  The last byte occupied by the datatype.

  .. math::
     :label: eq:upperbound

     \textrm{UB}[m] = \max_{j}[\textrm{Displacement}_{j} + \texttt{sizeof}(\textrm{Datatype}_{j})] + \textrm{Padding}

Extent
  The amount of memory needed to represent the datatype, taking into account architecture-specific alignment.

  .. math::
     :label: eq:extent

     \textrm{Extent}[m] = \textrm{UB}[m] - \textrm{LB}[m]


The C language (and Fortran) *require* that the data occurs in memory at
well-defined addresses: the data needs to be aligned. The address, in bytes, of
any item must be a multiple of the size of that item in bytes. This is so-called
*natural alignment*.
For our ``Pair`` data structure the ``first`` element is an ``int`` and occupies
4 bytes. An ``int`` will align to 4 bytes boundaries: when allocating a new
``int`` in memory, the compiler will insert **padding** to reach the alignment
boundary. Indeed, ``second`` is a ``char`` and requires just 1 byte. This gives:

.. math::

   \begin{aligned}
     \texttt{Pair.first} &\rightarrow \textrm{Displacement}_{0} = 0, \quad \texttt{sizeof}(\texttt{int}) = 4 \\
     \texttt{Pair.second} &\rightarrow \textrm{Displacement}_{1} = 4, \quad \texttt{sizeof}(\texttt{char}) = 1
   \end{aligned}


To insert yet another
``Pair`` item, we first need to reach the alignment boundary with a padding of 3
bytes.
Thus:

.. math::

   \begin{aligned}
     \textrm{LB}[\texttt{Pair}] &= \min[0, 4] = 0 \\
     \textrm{UB}[\texttt{Pair}] &= \max[0+4, 4+1] + 3 = 8 \\
     \textrm{Extent}[\texttt{Pair}] &= \textrm{UB}[\texttt{Pair}] - \textrm{LB}[\texttt{Pair}] = 8
   \end{aligned}

.. figure:: img/E01-extent_and_size.svg
   :align: center

   The relation between **size** and **extent** of a derived datatype in the
   case of the ``Pair``.
   We show the address alignment boundaries with
   vertical :red:`red` lines. The lowerbound of the custom datatype is 4:
   ``first`` can be found with an offset of 4 bytes after the starting address.
   Notice the 3 bytes of padding, necessary to achieve natural alignment of
   ``Pair``.  The upperbound is 8: the *next* item of type ``Pair`` can be found
   with an offset of 8 bytes after the previous element.
   The total size is 5 bytes, but the extent, which takes the padding into
   account, is 8 bytes.

.. challenge:: Which of the following statements about the size and
               extent of an MPI datatype is true?

   1. The size is always greater than the extent

   2. The size and extent can be equal

   3. The extent is always greater than the size

   4. None of the above

.. solution::

   2. The size and extent can be equal when no padding is
      required. It's best not to rely on this even when it is true,
      because your code or compiler or MPI library can change.

MPI offers functions to query extent and size of its types: they all take a variant of the ``MPI_Datatype`` enumeration as argument.

.. signature:: |term-MPI_Type_get_extent|

   Returns the lower bound and extent of a type.

   .. code-block:: c

      int MPI_Type_get_extent(MPI_Datatype type,
                              MPI_Aint *lb,
                              MPI_Aint *extent)

.. parameters::

   ``type``
     The datatype whose extent we're querying.
   ``lb``
     The lower bound of the datatype. ``MPI_Aint`` is a type designed to hold any valid address.
   ``extent``
     The extent of the datatype. ``MPI_Aint`` is a type designed to hold any valid address.

.. signature:: |term-MPI_Type_size|

   Returns the number of bytes occupied by entries in the datatype.

   .. code-block:: c

      int MPI_Type_size(MPI_Datatype type,
                        int *size)

.. parameters::

   ``type``
     The datatype whose extent we're querying.
   ``size``
     The number of bytes occupied by the entries in the datatype.


.. challenge:: Extents and sizes

   We will now play around a bit with the compiler and MPI to gain further
   understanding of padding, alignment, extents, and sizes.

   #. What are extents and sizes for the basis datatypes ``char``, ``int``,
      ``float``, and ``double`` on your architecture? Do the numbers conform to
      your expectations? What is the result of ``sizeof`` for these types?

      .. code-block:: c

         // char
         printf("sizeof(char) = %ld\n", sizeof(char));
         MPI_Type_get_extent(MPI_CHAR, &.., &..);
         MPI_Type_size(MPI_CHAR, &..);
         printf("For MPI_CHAR:\n  lowerbound = %ld; extent = %ld; size = %d\n", ..,
                 .., ..);

      You can find the file with the complete source code in the
      ``content/code/day-1/03_basic-extent-size/solution`` folder.

   #. Let's now look at the ``Pair`` data structure. We first need declare the
      data structure to MPI. The following code, which we will study
      in much detail later on, achieves the purpose:

      .. code-block:: c

         // build up the typemap for Pair
         // the type signature for Pair
         MPI_Datatype typesig[2] = {MPI_INT, MPI_CHAR};
         // how many of each type in a "block" of Pair
         int block_lengths[2] = {1, 1};
         // displacements of data members in Pair
         MPI_Aint displacements[2];
         // why not use pointer arithmetic directly?
         MPI_Get_address(&my_pair.first, &displacements[0]);
         MPI_Get_address(&my_pair.second, &displacements[1]);

         // create and commit the new type
         MPI_Datatype mpi_pair;
         MPI_Type_create_struct(2, block_lengths, displacements, typesig, &mpi_pair);
         MPI_Type_commit(&mpi_pair);

      What are the size and the extent? Do they match up with our pen-and-paper calculation?
      Try different combinations of datatypes and adding other fields to the ``struct``.

      You can find the file with the complete source code in the
      ``content/code/day-1/04_struct-extent-size/solution`` folder.


.. typealong:: Extents and the ``count`` parameter

   Let us reiterate: the extent of a custom datatype *is not* its size. The
   extent tells the MPI runtime how to get to the **next** item in an array of a
   given type, much like a *stride*.

   We can send an array of ``n`` ``int``-s with a single |term-MPI_Send|:

   .. literalinclude:: code/snippets/send_n.c
      :language: c
      :lines: 33-45

   or with ``n`` such calls:

   .. literalinclude:: code/snippets/n_send.c
      :language: c
      :lines: 35-46

   In the latter case, we must program explicitly how to get the next element in
   the array by using the extent of the datatype.

Any type you like: datatype constructors in MPI
-----------------------------------------------

The typemap concept allows us to provide a *low-level* description of any compound
datatype.  The class of functions ``MPI_Type_*`` offers facilities for *portable* type
manipulations in the MPI standard.
At a glance, each custom datatype goes through a well-defined lifecycle in an MPI application:

- We *construct* our new datatype with a **type constructor**. The new type will
  be a variable with ``MPI_Datatype`` type.
- We *publish* our new type to the runtime with |term-MPI_Type_commit|.
- We *use* the new type in any of the MPI communication routines, as needed.
- We *free* the new type from memory with |term-MPI_Type_free|.


.. figure:: img/E01-type-life-cycle.svg
   :align: center

   The lifecycle of user-defined datatypes in MPI. Calling any of the type
   constructors will create an object of type ``MPI_Datatype`` with the
   user-defined typemap. Before using this custom datatype in message passing,
   it needs to be published with |term-MPI_Type_commit|: the typemap is made
   known to the runtime, allowing it to handle messages of the new custom type.
   The programmer must take care to free the custom datatype object.


It is not always necessary to go all the way down to a typemap to construct new
datatypes in MPI.  The following types can be created with convenience
functions, side-stepping the explicit computation of a typemap. In MPI
nomenclature, these types are:

Contiguous
  A homogeneous collection of a given datatype. The returned new type will
  describe a collection of ``count`` times the old type. Elements are
  contiguous: :math:`n` and :math:`n-1` are separated by the extent of the old
  type.

  .. signature:: |term-MPI_Type_contiguous|

     .. code-block:: c

        int MPI_Type_contiguous(int count,
                                MPI_Datatype oldtype,
                                MPI_Datatype *newtype)

Vector
  A slight generalization of the contiguous type: ``count`` elements in the new
  type can be separated by a stride that is an arbitrary multiple of the extent
  of the old type.

  .. signature:: |term-MPI_Type_vector|

     .. code-block:: c

        int MPI_Type_vector(int count,
                            int blocklength,
                            int stride,
                            MPI_Datatype oldtype,
                            MPI_Datatype *newtype)

Hvector
  Yet another generalization of the contiguous datatype. The separation between
  elements in a hvector is expressed in bytes, rather than as a multiple of the
  extent.

  .. signature:: |term-MPI_Type_create_hvector|

     .. code-block:: c

        int MPI_Type_create_hvector(int count,
                                    int blocklength,
                                    MPI_Aint stride,
                                    MPI_Datatype oldtype,
                                    MPI_Datatype *newtype)

Indexed
  This type allows to have non-homogeneous separations between the elements.
  Each displacement is intended as a multiple of the extent of the old type.

  .. signature:: |term-MPI_Type_indexed|

     .. code-block:: c

        int MPI_Type_indexed(int count,
                             const int array_of_blocklengths[],
                             const int array_of_displacements[],
                             MPI_Datatype oldtype,
                             MPI_Datatype *newtype)

Hindexed
  This is a generalization of the indexed type analogous to the hvector.  The
  non-homogeneous separations between the elements are expressed in bytes,
  rather than as multiples of the extent.

  .. signature:: |term-MPI_Type_create_hindexed|

     .. code-block:: c

        int MPI_Type_create_hindexed(int count,
                                     const int array_of_blocklengths[],
                                     const MPI_Aint array_of_displacements[],
                                     MPI_Datatype oldtype,
                                     MPI_Datatype *newtype)


Before using the output parameter ``newtype``, it needs to be "published" to the
runtime with |term-MPI_Type_commit|:

.. signature:: |term-MPI_Type_commit|

   .. code-block:: c

      int MPI_Type_commit(MPI_Datatype *type)


``newtype`` is a variable of type ``MPI_Datatype``. The programmer must
ensure proper release of the memory used at the end of the program by calling
|term-MPI_Type_free|:


.. signature:: |term-MPI_Type_free|

   .. code-block:: c

      int MPI_Type_free(MPI_Datatype *type)


In practice, none of the previous convenience constructors might be suitable for
your application. As we glimpsed in a previous challenge, the general type
constructor |term-MPI_Type_create_struct| will suit your needs:

.. signature:: |term-MPI_Type_create_struct|

   .. code-block:: c

      int MPI_Type_create_struct(int count,
                                 const int array_of_block_lengths[],
                                 const MPI_Aint array_of_displacements[],
                                 const MPI_Datatype array_of_types[],
                                 MPI_Datatype *newtype)

.. parameters::

   ``count``
     Number of fields (*blocks* in MPI nomenclature) of the datatype. This is
     the length of the ``array_of_block_lengths``, ``array_of_displacements``,
     and ``array_of_types`` parameters.

   ``array_of_block_lengths``
     Number of elements in each field of the datatype.

   ``array_of_displacements``
     Displacements, in bytes, for each field of the datatype.

   ``array_of_types``
     Types for each field of the datatype, *i.e.* the type signature.

   ``newtype``
     The new datatype.



.. typealong:: The MPI version of the ``Pair`` datatype

   We saw code for this earlier on, but without explanation. Let's dive into it now!
   You can find the file with the complete source code in the
   ``content/code/day-1/04_struct-extent-size/solution`` folder.

   ``Pair`` has two fields, hence ``count = 2`` in the call to
   ``MPI_Type_create_struct``. All array arguments to this function will have
   length 2.
   The type signature is:

   .. code-block:: c

      MPI_Datatype typesig[2] = {MPI_INT, MPI_CHAR};

   We have one ``int`` in the ``first`` field and one ``char`` in the ``second``
   fields, hence the ``array_of_block_lengths`` argument is:

   .. code-block:: c

      int block_lengths[2] = {1, 1};

   The calculation of displacements is slightly more involved.  We will use
   ``MPI_Get_address`` to fill the ``displacements`` array. Notice that its
   elements are of type ``MPI_Aint``:

   .. code-block:: c

      MPI_Aint displacements[2];
      MPI_Get_address(&my_pair.first, &displacements[0]);
      MPI_Get_address(&my_pair.second, &displacements[1]);

   We *cannot use* pointer arithmetic to compute displacements. Always keep in
   mind that your program might be deployed on heterogeneous architectures: you
   have to program for correctness and portability.

   We are now ready to call the type constructor and commit our type:

   .. code-block:: c

      MPI_Datatype mpi_pair;
      MPI_Type_create_struct(2, block_lengths, displacements, typesig, &mpi_pair);
      MPI_Type_commit(&mpi_pair);

   And clean up after use, of course!

   .. code-block:: c

      MPI_Type_free(&mpi_pair);


.. challenge:: More message passing Pokémons

   We will revisit the Pokémon example from above using custom datatypes.

   You can find a scaffold for the code in the
   ``content/code/day-1/07_pokemon-type-create-struct`` folder.
   You will have to complete the source code to compile and run correctly:
   follow the hints in the source file.  A working solution is in the
   ``solution`` subfolder.

   .. tabs::

      .. tab:: Pokémons, again!

         #. Define the C ``struct`` for a pokémon. This has to contain:

            - The attacking pokémon's name: a ``char`` array.
            - How many life points it has: a ``double``.
            - The damage its attack will inflict: an ``int``.
            - A damage multiplier: a ``double``.

         #. Create its corresponding MPI datatype.
         #. Print it out on the receiving process.

         Compile with::

           mpicc -g -Wall -std=c11 pokemon-type-create-struct.c -o pokemon-type-create-struct

         What happens if you don't commit the type?

      .. tab:: Superbonus

         Somehow the rules have changed: you can use multiple pokémon's in your round!
         Modify your code to broadcast an array of 4 pokémons as a new type.



See also
--------

* The lecture covering MPI datatypes from EPCC is available on `GitHub <https://github.com/EPCCed/archer2-MPI-2020-05-14/blob/master/slides/L10-derivedtypes.pdf>`_
* Chapter 5 of the **Using MPI** book by William Gropp *et al.* :cite:`Gropp2014-qf`
* Chapter 6 of the **Parallel Programming with MPI** book by Peter Pacheco. :cite:`Pacheco1997-qq`


.. keypoints::

   - Typemaps are essential to enable MPI communication of complex datatypes.
   - MPI offers many type constructors to portably use your own datatypes in
     message passing.
   - Usage of the type constructors can be quite involved, but you strictly
     ensure your programs will be portable.
