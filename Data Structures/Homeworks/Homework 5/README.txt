HOMEWORK 5: LINKED GRID


NAME:  < Simon Gibson >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

OFFICE HOURS:
WED : 6-750
THURS: 1-7:50

LINKS:
https://www.geeksforgeeks.org/linked-list-set-2-inserting-a-node/
https://stackoverflow.com/questions/15252002/what-is-the-past-the-end-iterator-in-stl-c
https://stackoverflow.com/questions/41352941/can-i-check-a-c-iterator-against-null
https://www.cplusplus.com/reference/list/list/splice/
https://stackoverflow.com/questions/55979935/concatenatee-two-lists-in-c-in-o1-complexity
https://www.tutorialspoint.com/list-splice-function-in-cplusplus-stl
https://stackoverflow.com/questions/16229729/printing-out-contents-of-a-list-from-the-c-list-library
https://stackoverflow.com/questions/3475152/why-cant-i-increment-a-variable-of-an-enumerated-type
http://www.cplusplus.com/forum/beginner/41790/
https://stackoverflow.com/questions/40979513/changing-enum-to-next-value-c11
https://stackoverflow.com/questions/31952627/c-how-to-get-a-pointer-to-the-current-object-in-another-class
https://stackoverflow.com/questions/14557657/linker-error-c-undefined-reference
https://stackoverflow.com/questions/17909343/is-multiplication-of-two-numbers-a-constant-time-algorithm

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 25 hours >
TUESDAY   :  5 HOURS 
WEDNESDAY :  8 HOURS
THURSDAY  : 12 HOURS


COMPLEXITY ANALYSIS:
Give the big 'O' notation for each function (or function group) below
assuming the grid is w nodes wide and h nodes high.  Write one or two
sentences justifying each answer.


NOTE TO TA:
    I use w and h interchangeabl with (w-1)(h-1) in my analysis, because
    it simplifys every time, thus even if i iterate (w-1) times, if w is
    very large, than the -1 is negligeable

Grid constructor - O(hw)
    The Grid constructor creates h head nodes, and for each head node,
    creates w "list" nodes for the current row. The creation and 
    asssignment of Nodes and node member variables are O(1), THURS
    O(h(w)) = O(hw). Including custom function assign_corners O(hw),
    we have O(hw + hw) = O(hw)

Grid copy constructor - O(hw)
    Calls copyGrid() which is O(hw), this is because copyGrid() creates
    h copies of head nodes, and for each head node, creates w copies of
    the node in each row of Grid old. Thus O(h(w)) = O(hw). 
    assign_corners() is also called, thus copy constructor is O(hw)

Grid assignment operator - O(hw)
    The assignment operator calls copyGrid() in non self-assignment 
    cases, which we found is O(hw), additionally it calls destroy_grid()
    which loops over head nodes, and for each head of the row, loops
    over the current node rightwise and deletes the previous; Thus O(hw)
    Then, the two O(hw)'s add and simplify to O(hw)

Grid destructor - O(hw)
    Addressed in the grid assignment operator, we found that the time
    complexity is O(hw)

Grid getWidth - O(1)
    returns a single member variable
Grid getHeight- O(1)
    returns a single member variable
Grid getSize - O(1)
    Performs a single multiplaction operation, which is O(1)
    and returns the result, O(1 + 1) = O(1)

Grid get - O(i + j)
    Uses getAtLoc (indexing function). getAtLoc runs in O(i+ j), where i is 
    first index and j is second. This is because getAtLoc runs two loops to 
    move right i times and down j times from upper_left. Thus get() runs in
    O(i + j), because a return and member variable access (both O(1)) are
    also used, get runs in O(i+j)

Grid set - O(i + j)
    Used getAtLoc and sets the value at the result of getAtLoc to v.

Grid print - O(wh)
    Creates a head node for each row and loops rightwise in each row by 
    w iteratiorns. Also does two cout operations O(1), thus print is
    O(wh)

Grid reset - O(wh)
    Loops over each row via head node, and in each row loops w times right
    and at each current node sets the value, thus O(hw)

Grid clear - O(wh)
    Calls destroy_grid, which was found to be O(wh) above, thus clear is O(wh)

Grid join O(h) Alone , O(wh) including assign_corners()
    By itself, starts at topright of grid1 and topleft at grid2, and then loops
    downwise and links the two adjacent nodes. Thus join is O(h). However since 
    assign_corners is called, which is O(wh), then join becomes O(wh) 

Grid stack - O(w) alone, O(wh) including assign_corners()
    Similar to join, starts at topleft of grid1 and bottomleft of grid2, and then
    loops rightwise and links the two adjacent nodes. Thus stack is O(w). Again 
    because of the calling of assign_corners, the overruling complexity is O(wh)

Grid chop - O(h + w) alone, O(wh) including assign_corners()
    Starts with an iterator, and moves it to the top, which on average is h/2 moves,
    which becomes O(h) when iterator not at top to begin with. Then in most cases
    (height > 1), iterates down h times to break the link between current and the node
    to the right of current. Lastly, iterates across the new chopped off piece to find its 
    new width, which can be anywhere from (1,w-1), thus O(w-1) = O(w). The the 
    overally complexity is O(h+h+w) = O(2h + w) = O(h + w) 
    There are two assign corners present, which is O(2hw) = O(hw). 

Grid lift - O(w + h) alone, O(wh) including assign_corners()
    Similar to chop, but moves left until beginning, O(w). Then moves all the way
    right and breaks the links of the node above it and current one, O(w). Lastly,
    iterates up the lifted piece to find its new height, O(h). Including assign_corners(),
    we have O(hw), wihtout we have O(w+w+h) = O(w+h).

GridIterator constructor - O(1)
    Sets member variable values

Grid begin_upper_left O(1)
    Creates a new iterator object of the node pointer and returns it

Grid begin_upper_right O(1)
    Creates a new iterator object of the node pointer and returns it

Grid begin_lower_left O(1)
    Creates a new iterator object of the node pointer and returns it

Grid begin_lower_right O(1)
    Creates a new iterator object of the node pointer and returns it

Grid end O(1)
    creates a new iterator obect of NULL pointer and returns it

GridIterator operator* O(1)
    access the member variable of node iterator is pointing to,
    and returns it

GridIterator left O(1)
    reassigns member variable ptr to the node to the left of pointer
    and returns current instance dereferenced

GridIterator right O(1)
    reassigns member variable ptr to the node to the left of pointer
    and returns current instance dereferenced

GridIterator up O(1)
    reassigns member variable ptr to the node above pointer
    and returns current instance dereferenced

GridIterator down O(1)
    reassigns member variable ptr to the node below pointer
    and returns current instance dereferenced

Grid begin_snake O(1)
    Creates an iterator object of the grids upper_left node pointer,
    and updates two member variables, and returns created iterator.
    All operations are O(1)

Grid end_snake O(1)
    Creates an iterator of the deference of pointer at end of snaking,
    which happens to be NULL, also has two conditional statements with
    basic arithmetic. All operations are O(1).

Grid begin_spiral O(1)
    Creates grid iterator of upperleft node and current grid, and then
    updates the iterators member variables and returns the iterator,
    all operations are O(1)

Grid end_spiral O(1)
    creates a iterator of a NULL POINTER, useful for spiral in ++
    operator

GridIterator operator++ for snake O(1)
    Has 4 conditionals, each of which have 2 conditions and, if passed,
    reassign the iterators ptr member variable. If at the edges, changes
    direction by flipping a boolean. All operations are O(1).

GridIterator operator-- for snake (Extra Credit?)

GridIterator operator++ for spiral - O(1)
    has a conditional to check if total spiral moves is < size - 1,
    which is the end condition for the spiral. If the iterator can move,
    it goes into the condtional of correct direction, and then checks if
    the iterator is at a corner or not. If at a corner, it rotates the direction
    90 degrees and moves in that direction once. If not at corner, it continues on
    current path. Each direction condtional is O(1), and the direction rotation is
    also O(1), as is the 4 iterator movement funtions and the corner reassignments.
    Thus the ++ operator is a large O(1), where numerous O(1) operations are called.

GridIterator operator-- for spiral (Extra Credit?)


OPTIONAL EXTRA CREDIT:
Describe your implementation choices here.  




MISC. COMMENTS TO GRADER:  
TA in office hours gave me the all clear to use ENUM Direction
for my spiral iterator


