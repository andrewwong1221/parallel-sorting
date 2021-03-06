Parallel Sorting
================

An analysis of various parallel sorting algorithms for my term project in CSC258 at the University of Rochester. Please see the writeup for additional details.

To run the program, compile using the makefile specified for the architecture and
run:
    bin/sort [-v] -n <threads> -s <array_size>

## Sorts implemented
* Radix Sort
* Merge Sort
* Bitonic Merge Sort
* Insertion Sort
* Sample Sort

References
----------
1. [A Comparison of Parallel Sorting Algorithms on Different
Architectures](http://parasol.tamu.edu/publications/download.php?file_id=191)

2. [Searching for the Sorting Record: Experiences in Tuning NOW-Sort](http://pages.cs.wisc.edu/~dusseau/Papers/spdt.ps)

3. [WIND-sort](http://research.cs.wisc.edu/wind/Publications/wind-sort-tr.pdf)

4. [A novel sorting algorithm for many-core architectures based on adaptive bitonic sort](http://comsys.informatik.uni-kiel.de/wp-content/uploads/2012/02/2012-Peters-IPDPS-crv.pdf)

5. [StackOverflow List of Sorting Papers](http://stackoverflow.com/questions/3969813/which-parallel-sorting-algorithm-has-the-best-average-case-performance)
