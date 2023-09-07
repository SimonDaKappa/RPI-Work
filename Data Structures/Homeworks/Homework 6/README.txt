HOMEWORK 6: CARCASSONNE RECURSION


NAME:  < insert name >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
the forum, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
DS OFFICE HOURS:
TUESDAY 6-750PM
WEDNESDAY 6-750PM / 10-12 LAB

https://stackoverflow.com/questions/1765171/instead-of-null-should-i-write-0x0-or-0
https://stackoverflow.com/questions/46418848/null-pointer-doesnt-address-to-0x0-location-in-cpp
https://stackoverflow.com/questions/7970857/java-shifting-elements-in-an-array
https://www.geeksforgeeks.org/core-dump-segmentation-fault-c-cpp/?ref=leftbar-rightbar
https://stackoverflow.com/questions/2902064/how-to-track-down-a-double-free-or-corruption-error
https://stackoverflow.com/questions/32391561/how-to-catch-exception-caused-in-c-in-python
https://lingpipe-blog.com/2011/07/01/why-is-c-so-fast/
https://en.wikipedia.org/wiki/Template_metaprogramming
https://stackoverflow.com/questions/2902064/how-to-track-down-a-double-free-or-corruption-error
https://cs.stackexchange.com/questions/56176/a-graph-search-time-complexity
And many more I had too many tabs and deleted them.


Remember: Your implementation for this assignment must be done on your
own, as described in "Collaboration Policy and Academic Integrity".



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < insert 20 hours >
MONDAY    : 5 HOURS
TUESDAY   : 4 HOURS
WEDNESDAY : 3 HOURS
THURSDAY  : 5 HOURS
FRIDAY    : 3 HOURS



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (h and w)? 
The number of tiles (t)? 
The number of road (r) and city (c) edges? 
The number of duplicate tiles?
Whether rotations are allowed?  
Etc. 

read_tile():

My Algorithm recursively attempts to place each tile. For each tile, it checks every
single point on the board and its 4 side-side connections for valid connections.
Each side-side connection check( canPlaceSomeDirection() ) is O(1), as it is composed
of a concrete amount of conditionals and simple accessor statements. Provided that a 
solution is guaranteed. Each tile moves h * w times in the worst case, and so if 
a list of tiles is t long, then the last tile can move h * w times, and then 
the second to last tile can move h*w times, but for each time the second to last
tile moves, the last tile can move h*w times, and so on and so on. Thus, 
the total amount of moves in the worst case is (h*w)^t. Duplicate tiles do not
affect my algorithm, as it does not work. When a possible solution needs to be checked,
the helper function validSolution() runs a for loop of total length h*w, and at each
spot, checks to make sure that the 4 side-side connections are valid ( O(1) as stated
earlier). In the worst case, when a board is a solution, the complexity is O(h*w) for 
validSolution(). The number of road and city edges do not effect the time, as every tile
has all 4 corners checked regardless. Similarly, duplicate tiles are all treated as 
individual unique tiles, so they do not reduce run time in my algorithm. Assuming that v 
possible valid boards need to be checked, we have a total time complexity of O((h*w)^t + v(h*w)). 
In cases where v is negligable to the boardsize, or a solution is found rather quickly, 
like in puzzle1, the time complexity is more simply O((h*w)^t), as 1(h*w) 
is very small compared to (h*w)^4.




SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles with various command line arguments.

I was unable to get rotational solutions and multiple solutions.
For the provided examples 1-7, those that could be solved (not 3),
all were solved in under a second. I did notice a slight improvement in
the 6x6 puzzles when limitting the board to the minimum size (ie 3x5 for puzzle9).
I imagine if my program solved for numerous solutions and rotations, limiting the size
would yield massive improvements, as my crude implementation does a ton of operations at 
every single index of the vector<vector<Tile*>>. Some performance improvements I wished to include if 
I had the time were: slides, reduntant check removal, 4 side redundancy.
For the slide, if my total number of tiles  on the board was larger than half of the tile count in
the puzzle, if you could place a piece in a direction, but it would be out of bounds and the opposite row/colum
was free, I would shift the entire board so that I would not have to backtrace and possibly reconstruct numerous
failed boards in the process. For the redunancey checks, if there was only one tile on the board, if the next
tile would not attach to either of the 4 sides of the first tile, instead of chekcing every single combination
of the first and second tile at different locations of the board (which would all fail), it would either
move onto rotations or return no solution. Additionally, I wished to add a secondary 2D vector or booleans, 
which for attempt to place a Tile, would be true at [i][j] if it had already been checked to be false
on at least one edge-edge connection or a piece was already at [i][j], thereby preventing a redundant check.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
