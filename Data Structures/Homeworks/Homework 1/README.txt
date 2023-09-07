HOMEWORK 1: ASCII FONT ART


NAME:  < Simon Gibson >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
the forum, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
(For reference on C vs C++ style and STD string)
https://www.geeksforgeeks.org/char-vs-stdstring-vs-char-c/ 
https://stackoverflow.com/questions/2158943/split-string-into-array-of-chars
https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector
https://stackoverflow.com/questions/54032945/error-cannot-bind-non-const-lvalue-reference-of-type-int-to-an-rvalue-of-typ
https://www.geeksforgeeks.org/stdstringreplace-stdstringreplace_if-c/
https://stackoverflow.com/questions/2158943/split-string-into-array-of-chars
https://www.cplusplus.com/reference/string/string/substr/
https://stackoverflow.com/questions/54429231/how-to-fix-stdlogic-error-what-basic-string-m-construct-null-not-valid
https://stackoverflow.com/questions/2896600/how-to-replace-all-occurrences-of-a-character-in-string
https://en.cppreference.com/w/cpp/algorithm/replace
https://stackoverflow.com/questions/50753559/compiler-error-void-value-not-ignored-as-it-ought-to-be-in-c-programming?noredirect=1&lq=1
https://stackoverflow.com/questions/877523/error-request-for-member-in-which-is-of-non-class-type
- My apology to the TA, but i forgot their name (Friday Office Hours help with debugging)
-I stopped pasting stackoverflow links of simple questions around 3 hours in, but it was 
-a lot more of the same




Remember: Your implementation for this assignment must be done on your
own, as described in "Collaboration Policy and Academic Integrity".
------------------
HOMEWORK PLANNING:
------------------
         Homework part 1: Planning Display() Function
         1. Break down argv[3] into individual chars (create vector<char> and pushback each char with some substring function maybe?)
            There has to be a much more efficient way
            UPDATE: I can create a vector<char> characters(str.begin(), str.end()) after converting argc[3] into a STD::string 
         2. Create new vector of ASCII Bitmap conversions {
            a. For each letter converted, loop over that vector<string> to replace the foreground and background with inputted characters.
            b. Replacing back and foreground {
                i. I need to look into replacement methods; Check if std::string class has functions similar to python like .replace
                ii. Seems like std::string does infact have a method to do this
                iii. I dont want to loop again in this loop, but I dont see another way to do this easily.
                }
            }

            c. Im having troubles with my std::replace function, but for now I'm just going to restrict my foreground and background characters to char only, 
               maybe the autograder has multi-byte characters but I'll solve that when I need to


         3. Create code to cout ASCII art {
            a. Most likely O(n^2), at least easiest way I can think of
            b. Kind of backwards, but loop over rows of ASCII messages first, and inside that loop do another 
            loop that iterates over vector. (Inside out so that I can ::endl after each row to construct output)
            c. NVM; very dumb idea, just loop regularly
            }

        Part 1: ~95% Complete,
        TODO: 
            Clean Up Code,
            Review Comments,
            Remove Debug Flags
            Rewrite portion that would allow different fore and backgrounds, seems to have a lot of errors 
                Possible Solution: Inclusion of delimiters, so that c++ doesnt take certain symbols as 
                input arguments but rather as a character.

        
        Homework part 2: planning read() Function
        1. Getting ASCII art from file
            a. ifstream 
        
        1.5.Finding foreground and background
            a. Loop over chunked_bitmap
            b. For each bitmap, background character is given by bottom line, so loop over rows until you find cha
               -racter that isnt background, and set it to foreground
            c. quit loop to save processing power
        
        
        2. Chopping input into useable blocks {
            a. Get needed block width from bitmap_letters (nvm I declared them in main i can just pass by value them in)
            b. Loop over Columns and then rows to Chop up Text into proper sized blocks for text recognition
                i. Make a column iterator inside loop that resets it to chunk width beginning until height is completely iterated over,
                   then go onto next 'chunk' of columns

            c. UPDATE: Rewrote this entire section a couple of times, previous planning outdated.
       
       
        3. Standardizing Foreground and Background,
            a. Pretty simple, just a loop over rows,cols of a chunked_bitmap and replacing the input back/foreground
               with standard.
        
        4. Character Recognition (This is gonna run realllllllly slow, triple loops seems only solution to me)
            a. Loop over bitmap_letters 
            b. For each bitmap, double for loop over row and columns and [i][j] compare by index each character
            c. For comparisons, include a percent correctness, if 100% correct, find the index of bitmap and use it to cast int to ascii.

        PART 2 NOTES:
        BITMAP LETTERS ISNT ASCII FROM [0][32] -> in for loop (int ascii = 32; ascii <= 126; ascii++)

        3

        Rethinking Read():
        1. Get ASCII art from file and initialize to vector<strings>
        1.5 Finding background/foreground
        2.Chunking
        3. No need to standardize background? maybe just check if chunk[row][col] == foreground && bitmap[row][col] == '#' a
           and vice-versa for background character, Problem : goes back to 4 loops, which I assume are slower 
           than a triple and a double loop 
        4.




ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 11-12 Hours >
Monday: 4 Hours
Tues:  30 Minutes
Wed:    2 Hours
Thurs:  3 Hours
Fri:    2 Hours


EXTRA CREDIT: KERNING 
Describe your implementation & paste in interesting example output
with & without kerning.  Please be concise!



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


