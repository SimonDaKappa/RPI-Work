HOMEWORK 10: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  < Simon Gibson >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 15 hours >



NAIVE ALGORITHM:

Big `O' Notation: The naive algorithm compares each pixel against every other pixel, so there are 
  n^4 comparisons, where n is the size of the side of the square of pixels. The rest of the operations
  are mainly O(1) accessors and sqrt calculations, which hardly affect run time
  Thus overally time compelxity is O(n^4)

Timing Experiment Data: All data uses the real time
5x5   : .009s
10x10 : .017s
30x30 : .060s
100^2 : .515s
300^2 : 45.0s
1000^2:
Discussion: The jump from 100^2 to 300^2 was massive time wise, wehre 100^4 is 1/81
  of 300^4, and the time is accurate where .515 ~= 45/81



IMPROVED ALGORITHM: n = side length, b = # black pixels

Big `O' Notation: The alogrithm starts by finding all the black pixels, an O(n^2) operation,
  which finds b black pixels. Next it iterates over the entire board, and for each pixel, 
  compares it to every black pixel, so a time complexity of O(n^2*b) for the comparison.
  Again there is little else that contributes to time complexity outside of these comparisons
  Thus we have time complexity o(n^2 + bn^2) = O(bn^2). However, since b is a fraction of n, we have 
  O(n^3)

Timing Experiment Data:
5x5   : .009s
10x10 : .010s
30x30 : .012s
100^2 : .080s
300^2 : 16.0s
1000^2:

Discussion: The implementation was actually quite accurate to estimations.
  Every data set larger than 10x10 was within 10% of just taking the naive's
  time and raising it to the ^(3/4). The smaller data sets propably got overriden
  with overhead that is negligable in larger sets.



FAST MARCHING METHOD (with a map): 

Big `O' Notation: The algorithm again finds all black pixels O(n^2). Next it
  propogates the distance to each of the 0-8 surrounding pixels for each black pixel. This operation
  contains quite a bit of calculative overhead, but essentially we have a time complexity of O(b*8),
  where b is the number of black pixels. Each surrounding pixel that isnt known/black is added to the
  back of priority queue and percolated up. Percolating up has a maximum log_2(q) iterations/swaps,
  where q is the size of the priority queue. For calculations sake say q = n^2 (the maximum size possible).
  Then for each pixel surround the black pixels, we perform a percolation that is O(log2(q)). Afterwards,
  we continue to propogate for each pixel in the priority queue. The maximum amount of propogations is
  8*n^2, so in worst case, where every propogation requires a percolation, we have 8(log2_n)^2 complexity.
  Then our overall time complexity is o(n^2 + 8b(log2_n)^2) = O( n * (log2(n)^2 ) if b is a large fraction
  of n, or O(b * (log2(n)^2)) is b a small fraction of n.

Timing Experiment Data: Could not successfully run

Discussion: 



DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Big `O' Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






