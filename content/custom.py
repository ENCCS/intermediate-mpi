# -*- coding: utf-8 -*-

# add the MPI function to reference in the glossary here. This skullduggery is
# necessary to get consistent monospace formatting of the function
#
# Communicators and groups
lesson_comms = [
    "MPI_Comm_split",
    "MPI_Comm_create",
    "MPI_Comm_free",
    "MPI_Comm_rank",
    "MPI_Comm_size",
    "MPI_Comm_group",
    "MPI_Group_free",
    "MPI_Cart_create",
]
# derived datatypes
lesson_dd = [
    "MPI_Type_get_extent",
    "MPI_Type_size",
    "MPI_Pack",
    "MPI_Unpack",
    "MPI_Type_contiguous",
    "MPI_Type_vector",
    "MPI_Type_indexed",
    "MPI_Type_create_hvector",
    "MPI_Type_create_hindexed",
    "MPI_Type_create_struct",
    "MPI_Type_commit",
    "MPI_Type_free",
    "MPI_Op_create",
    "MPI_Op_free",
]
# remote memory access
lesson_rma = [
    "MPI_Get",
    "MPI_Put",
    "MPI_Accumulate",
    "MPI_Win_create",
    "MPI_Win_allocate",
    "MPI_Win_allocate_shared",
    "MPI_Win_create_dynamic",
    "MPI_Win_fence",
    "MPI_Win_post",
    "MPI_Win_start",
    "MPI_Win_complete",
    "MPI_Win_wait",
    "MPI_Win_lock",
    "MPI_Win_unlock",
]
# collectives
lesson_coll = [
    "MPI_Allgatherv",
]
# non-blocking
lesson_non_blocking = [
    [ "MPI_Isend", 63],
    [ "MPI_Irecv", 63],
    [ "MPI_Wait", 64],
    [ "MPI_Waitany", 66],
    [ "MPI_Waitsome", 66],
    [ "MPI_Waitall", 66],
    [ "MPI_Test", 64],
    [ "MPI_Testany", 66],
    [ "MPI_Testsome", 66],
    [ "MPI_Testall", 66],
#    [ "MPI_", ],
]
# threads
lesson_threads = []

MPI_functions = lesson_comms + lesson_dd + lesson_rma + lesson_coll + lesson_threads
MPI_functions_2 = lesson_non_blocking

abbr_and_term = """
.. |{function}| replace:: ``{function}``
.. |term-{function}| raw:: html

   <a class="reference internal" href="../quick-reference/#term-{function}"><span class="xref std std-term"><code class="docutils literal notranslate">{function}</code></span></a>
"""

impls = """
.. |{function}-implementors_docs| raw:: html

   <p>Documentation from implementors:</p>
   <div>
   <ul class="simple">
   <li><p><a class="reference external" href="https://www.mpich.org/static/docs/latest/www3/{function}.html">MPICH</a></p></li>
   <li><p><a class="reference external" href="https://www.open-mpi.org/doc/current/man3/{function}.3.php">OpenMPI</a></p></li>
   </ul>
   </div>
"""

impls_2 = """
.. |{function}-implementors_docs| raw:: html

   <p>Documentation from implementors:</p>
   <div>
   <ul class="simple">
   <li><p><a class="reference external" href="https://www.mpich.org/static/docs/latest/www3/{function}.html">MPICH</a></p></li>
   <li><p><a class="reference external" href="https://www.open-mpi.org/doc/current/man3/{function}.3.php">OpenMPI</a></p></li>
   </ul>
   </div>
   <p>Documentation in the standard:</p>
   <div>
   <ul class="simple">
   <li><p><a class="reference external" href="https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report/node{id}.htm#Node{id}.html">MPI standard 3.1</a></p></li>
   </ul>
   </div>
"""


def MPI_glossary():
    # abbreviations and terms for the glossary
    glossary_helper = "\n".join(
        [abbr_and_term.format(function=f) for f in MPI_functions + MPI_functions_2]
    )
    glossary_helper += "\n"
    glossary_helper += "\n".join(
        [abbr_and_term.format(function=f) for f,id in MPI_functions_2]
    )

    # documentation string from implementors
    implementors_docs = "\n".join([impls.format(function=f) for f in MPI_functions])
    implementors_docs += "\n"
    implementors_docs += "\n".join([impls_2.format(function=f,id=id) for f,id in MPI_functions_2])

    # include all customisation in the rst_epilog, so it's available everywhere
    return glossary_helper + implementors_docs
