# -*- coding: utf-8 -*-

# add the MPI function to reference in the glossary here. This skullduggery is
# necessary to get consistent monospace formatting of the function. Each list
# entry should be a list of a string of the name of the MPI function and an
# integer of the node number of the MPI standard document webpage, e.g.
# 47 for https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report/node47.htm#Node47.
# Use a negative node number if unknown or inapplicable.
#
# Communicators and groups
lesson_comms = [
    ["MPI_Comm_split", 156],
    ["MPI_Comm_create", 156],
    ["MPI_Comm_free", 157],
    ["MPI_Comm_rank", 155],
    ["MPI_Comm_size", 155],
    ["MPI_Comm_group", 152],
    ["MPI_Group_free", 153],
    ["MPI_Group_excl", 153],
    ["MPI_Group_incl", 153],
]
# derived datatypes
lesson_dd = [
    ["MPI_Type_get_extent", 84],
    ["MPI_Type_size", 82],
    ["MPI_Pack", 92],
    ["MPI_Pack_size", 92],
    ["MPI_Unpack", 92],
    ["MPI_Type_contiguous", 79],
    ["MPI_Type_vector", 79],
    ["MPI_Type_indexed", 79],
    ["MPI_Type_create_hvector", 79],
    ["MPI_Type_create_hindexed", 79],
    ["MPI_Type_create_struct", 79],
    ["MPI_Type_commit", 86],
    ["MPI_Type_free", 86],
    ["MPI_Op_create", 115],
    ["MPI_Op_free", 115],
]
# remote memory access
lesson_rma = [
    ["MPI_Get", 270],
    ["MPI_Put", 269],
    ["MPI_Accumulate", 273],
    ["MPI_Win_create", 261],
    ["MPI_Win_allocate", 262],
    ["MPI_Win_allocate_shared", 263],
    ["MPI_Win_create_dynamic", 264],
    ["MPI_Win_fence", 280],
    ["MPI_Win_post", 281],
    ["MPI_Win_start", 281],
    ["MPI_Win_complete", 281],
    ["MPI_Win_wait", 281],
    ["MPI_Win_lock", 282],
    ["MPI_Win_unlock", 282],
    ["MPI_Win_free", 265],
    ["MPI_Win_test", 281],
    ["MPI_Win_attach", 264],
]
# collectives
lesson_coll = [
    ["MPI_Barrier", 100],
    ["MPI_Bcast", 101],
    ["MPI_Reduce", 111],
    ["MPI_Scatter", 105],
    ["MPI_Gather", 103],
    ["MPI_Allgather", 107],
    ["MPI_Alltoall", 109],
    ["MPI_Allgatherv", 107],
    ["MPI_Ibarrier", 127],
    ["MPI_Ireduce", 134],
]
# non-blocking
lesson_non_blocking = [
    ["MPI_Send", 47],
    ["MPI_Ssend", 57],
    ["MPI_Isend", 63],
    ["MPI_Irecv", 63],
    ["MPI_Wait", 64],
    ["MPI_Waitany", 66],
    ["MPI_Waitsome", 66],
    ["MPI_Waitall", 66],
    ["MPI_Test", 64],
    ["MPI_Testany", 66],
    ["MPI_Testsome", 66],
    ["MPI_Testall", 66],
    ["MPI_Ibsend", 63],
    ["MPI_Irsend", 63],
    ["MPI_Issend", 63],
]
# threads
lesson_threads = [
    ["MPI_Init_thread", 303],
    ["MPI_Query_thread", 303],
    ["MPI_Is_thread_main", 303],
    #    ["MPI_", 303],
]
# functions mentioned in passing in the lesson
other = [
    ["MPI_Recv", 50],
    ["MPI_Alloc_mem", 216],
    ["MPI_Free_mem", 216],
    ["MPI_Bsend", 57],
    ["MPI_Rsend", 57],
]

MPI_functions = (
    lesson_comms
    + lesson_dd
    + lesson_rma
    + lesson_coll
    + lesson_threads
    + lesson_non_blocking
    + other
)

abbr_and_term = """
.. |{function}| replace:: ``{function}``
.. |term-{function}| raw:: html

   <a class="reference internal" href="../quick-reference/index.html#term-{function}"><span class="xref std std-term"><code class="docutils literal notranslate">{function}</code></span></a>
"""

header = """
.. |{function}-implementors_docs| raw:: html
"""

impls = """
   <p>Documentation from implementors:</p>
   <div>
   <ul class="simple">
   <li><p><a class="reference external" href="https://www.mpich.org/static/docs/latest/www3/{function}.html">MPICH</a></p></li>
   <li><p><a class="reference external" href="https://www.open-mpi.org/doc/current/man3/{function}.3.php">OpenMPI</a></p></li>
   </ul>
   </div>"""

standard = """
   <p>Documentation in the standard:</p>
   <div>
   <ul class="simple">
   <li><p><a class="reference external" href="https://www.mpi-forum.org/docs/mpi-3.1/mpi31-report/node{id}.htm#Node{id}.html">MPI standard 3.1</a></p></li>
   </ul>
   </div>"""

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
        [abbr_and_term.format(function=function) for function, _ in MPI_functions]
    )

    # documentation string from implementors
    implementors_docs = ""
    for function, id in MPI_functions:
        implementors_docs += header.format(function=function)
        format_string = impls
        if id >= 0:
            format_string += standard
        implementors_docs += format_string.format(function=function, id=id)

    # include all customisation in the rst_epilog, so it's available everywhere
    return glossary_helper + implementors_docs


from sphinx_lesson.directives import _BaseCRDirective


class SignatureDirective(_BaseCRDirective):
    extra_classes = ["toggle-shown", "dropdown"]


class ParametersDirective(_BaseCRDirective):
    extra_classes = ["dropdown"]


class TypealongDirective(_BaseCRDirective):
    extra_classes = ["toggle-shown", "dropdown"]


DIRECTIVES = [SignatureDirective, ParametersDirective, TypealongDirective]
