HOMEWORK 8: QUAD TREES AND TREE ITERATION


NAME:  < insert name >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
https://www.geeksforgeeks.org/stdmax-in-cpp/
https://www.dreamincode.net/forums/topic/329312-invalid-use-of-template-name-without-an-argument-list/
https://www.tutorialspoint.com/data_structures_algorithms/tree_traversal.htm
https://stackoverflow.com/questions/40365732/preorder-traversal-of-a-quadtree
https://www.youtube.com/watch?v=1WxLM2hwL-U
https://stackoverflow.com/questions/759512/internal-typedefs-in-c-good-style-or-bad-style
https://stackoverflow.com/questions/759512/internal-typedefs-in-c-good-style-or-bad-style
https://submitty.cs.rpi.edu/courses/f21/csci1200/office_hours_queue
https://www.geeksforgeeks.org/iterative-preorder-traversal/
https://www.techiedelight.com/preorder-tree-traversal-iterative-recursive/
http://www.cplusplus.com/reference/algorithm/random_shuffle/

OFFICE HOURS:
  WED : 4-7:50 PM
  THUR: 3-6:00 PM

Remember: Your implementation for this assignment must be done on your
own, as described in "Collaboration Policy and Academic Integrity".



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 hours >



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the QuadTree operations and justify
your answer for the non trivial operations (please be concise!)
Analyze both the running time and the additional memory usage needed
(beyond the space allocated for the existing tree structure).  You may
assume that the tree is reasonably well balanced for all operations.

// I HEAVILY assume a balanced tree

n = the number of elements in the tree


size() - trivial getter function
  running time: O(1) 
  memory usage: O(1)

insert() - 
  traverses down the tree using (x,y) comparisons to get in the correct quadrant, 
  until an empty children index at the proper spot is available. Worst case it goes 
  to the bottom of the tree. Each layer of the tree is a fraction of log_4(n) of the 
  nodes. If found, creates a new node and a iterator pointing to that node. Since
  the function is recursive, we will have at max log_4(n) calls on the stack, so the 
  total memory usage is O(log4(n) + 1) = O(logn)

  running time: O(logn)
  memory usage: O(logn)

find() -
  Similarly to insert(), recursively calls and gets closer by one quadrant each call.
  At worst log(n) calls if a leaf node at bottom of tree. Each function call uses
  very  minimal memory, as it only recurses and creates a chain of returning the
  base case so O(1) memory

  running time: O(logn)
  memory usage: O(1)

height() / updateHeight() -
  Recursively calls itself on all the children, to a maximum depth of log(n) calls
  at each call computes the max O(3) = O(1) and adds 1 and returns it. Since
  each call uses 5 ints, we have a memory usage of o(5log(n)) = O(logn)

  running time: O(logn) 
  memory usage: O(logn)

begin() -
  Since preorder traversal, returns an iterator constructed from the root_ node.
  DepthIterator construction is an O(1) operation

  running time: O(1)
  memory usage: O(1)

end() -
  Since decrement operators are not required, end() is trivial and returns 
  an iterator pointing to a NULL Node*

  running time: O(1)
  memory usage: O(1)

bf_begin() -
  Since BFS traversal, begin is the root node, and returns a bf_iterator constructed
  from root_. BreadthIterators are not constructed trivially, but since the root_
  not has no parent, the constructor is simply O(1)

  running time: O(1)
  memory usage: O(1)

bf_end() -
  Since decrement operators are not required, bf_end() is trivial and returns 
  a bf_iterator pointing to a NULL Node*

  running time: O(1)
  memory usage: O(1)

operator++() -

  DepthIterator++ - 
    In best case, continues to traverse down the children of current node, starting
    at first nonnull child. If a leaf, has to go to parent and find a node to the right
    of the leaf. If the leaf is the 4th in children, have to go up a level higher to try 
    the leafs parents parents children. This can continue for log(n) - 1 times if worst case
    the 4th leaf of 4th leaf and on until it is the 3rd leaf of the root node. Average of O(1)
    and worse case of O(logn  - 1) = O(logn). Memory used is minimal, only two Node* so O(1)

  BreadthIterator - 
    First tries to move rightwards on current layer, an operation which performs in o(4) = O(1)
    time. Best case it can move right. Worst case the iterator is at the end of current layer,
    and needs to move to the next layer. Current becomes next and next becomes the children of 
    all nodes in current. This operation depends on the size of current, which at max is 4^(layer #)
    So at max, if row before last row, it will take up 1/4 of all total nodes. Thus the time complexity
    is at worst O(n) for finding the children. If there are any children, the iterator points to the first
    one in the vector. Since the current and next vectors are recycled, no additional memory is used
    beyond the two.

  running time: iterator - O(logn), bf_iterator - O(n) worst, O(1) best
  memory usage: iterator - O(1), bf_iterator - O(1)

operator*() - 
  returns ptr->pt for both iterator types, a trivial action

  running time: O(1)
  memory usage: O(1)

getLabel() - 
  returns the ptr->label for both iterator types, a trivial action

  running time: O(1)
  memory usage: O(1)

getDepth() -
  iterates upwards until the node doesnt have a parent. At worst iterator
  is pointing to a node at the very bottom of tree, logn iterations. A single
  int used to keep track for return.

  running time: O(logn)
  memory usage: O(1)

copy constructor -
  Reassigns primitive member variables O(1). Calls copy_tree(). Copy_tree() creates n nodes,
  where n is amount of nodes in the old QuadTree. Each recurse creates 1 node* and recurses
  for its children. Thus the function is called n times. Total time complexit of O(n)


  running time: O(n)
  memory usage: O(n)

assignment operator
  In non self assignment, calls destroy_tree(), where each call recurses 4 times. Thus a total
  call count of n. Each call deletes a node*. Afterwards does trivial reassignments
  and calls copy_tree. So total time of o(n + n + 1) = O(n). Copy_tree has memory
  use of O(n)


  running time: O(n)
  memory usage: O(n)

destructor
  Calls copy_tree on root_. Total recursion count of n.

  running time: O(n)
  memory usage: O(1)



EXTRA CREDIT:  TREE BALANCING
How does the point insertion order affect the shape of the resulting
QuadTree object? What are specific examples of the worst case and best
case?  Discuss your stratgy for reordering the input to rebalance the
tree.  Paste example output with and without your rebalancing.






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


