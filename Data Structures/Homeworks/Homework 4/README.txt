HOMEWORK 4: VISUAL DIFFERENCE LISTS


NAME:  < Simon Gibson >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
So Uh, I accidentally deleted this entire thing and had to redownload from submitty, and I lost
all my links. There were a lot of stack overflow, cppreference, and geeksforgeeks links, like a LOT.

OFFICE HOURS:
TUESDAY 6-750PM.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 23.5 >
MONDAY    : .5 HOURS
TUESDAY   :  5 HOURS
WEDNESDAY :  8 HOURS
THURSDAY  :  3 HOURS
SATURDAY  : 10 HOURs

ORDER NOTATION:
Give the order notation for each function below assuming
  w words in the first input file, and requiring
  i inserts, e erases, and r replace operations.
Write one or two sentences justifying each answer.


compute_diff - (default, non-optimal, non-recursive version)
Compute_diff runs in O(n). The function takes two iterators and performs a 
while loop over them, thus the loop is O(w) => O(n). Additionally, the insert
subgroup is made up entirely of constant time operations, (assignments, dereference,
list insert, list push_back, constructing an object with 3 variables, and incrementing).
Similarly, the erase subgroup ad replace subgroup are comprised of linear operations, wcich
all simplify to a multiple of n.
Thus the O() of compute_diff = O(n[(i + r + e)(1)]) = O(n),

apply_diff
Apply_diff runs in O(n^2). Similarly to compute_diff, it is comprised of a loop over a list
using iterators ( O(n) ) and subgroups within that loop. Each subgroup contains a list push_back,
construction of Diff object, and increment/decrement (O(1) operations). 
The only difference is the presence of std::advance(), which runs in O(n), because list iterators
are not random access. Thus apply_diff is O(n*n) = O(n^2)

invert_diff
Invert_diff runs in O(n^2). Like the previous to functions it contains a loop over a 
list using iterators and a subgroup. However 2/3 of these groups contain advance(),
thus in average case the subgroups run in O(n).Thus invert_diff runs in O(n*n)=O(n^2)


assert_same
assert_same runs in O(n) at average and worst, as this function is used to 
assert that lists are equal, more often than not they will be. Thus we enter a 
loop over the lists using iterators to compare element wise.Thus assert_same runs in O(n)

assert_same_diff
Similar to assert_same, assert_same_diff runs in O(n). The only difference
is that we compare member variable wise instead of element wise. However, 
Diff object accessors are O(1), thus assert_same is in O(n).


read_text
read_text runs in O(n) on average. For the assignment, the file will pass error checking,
and carry on over to an if else chain ( O(1) ). In case CHAR and case
WORD, pushback (O(1)) is called in a while loop,thus they are O(n). In the case of LINE, 
a while loop (O(n)) calls getLine (O(n)), thus in case LINEO(n^2). On average however, 
CHAR and WORD are used, thus I will say average is O(n).


write_text
write_text runs in O(n) on average. A while loop runs until the text is at it end,
thus the while loop runs for n iterations. The loop contains increment, ostream operators,
and == operators. Thus write_text is O(n).

read_diff
read_diff runs in O(n^2) time on average. When type = insert or replace, a double while
loop is iterated, which contains iostream operators and list push_back (O(1)).

write_diff
write_diff runs in O(n) time on average. A for loop of iterators over a list contains
accessors, iostream operations, and a JSON modiciation function (O(1) i think?).

render_diff
render_diff runs in O(n^2) at worst. An overarching while loop contains multiple cases,
where two cases contain another loop. The rest of the operations in the cases are assignments,
accessors, ==, and html_encode() (O(n)). Thus all cases contain at least one O(n) operation,
and render_diff is O(n*n) = O(n^2)

OPTIONAL EXTRA CREDIT - RECURSIVE SOLUTION FOR MINIMUM EDIT DISTANCE:

Include running times and interesting screenshots of the HTML
visualization for test cases you created to debug your solution.

What is the big notation of your function? (Use the same variables as
above)


compute_diff - (optimal, ecursive version)



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
