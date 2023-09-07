HOMEWORK 2: SPELLING BEE CLASSES


NAME:  < insert name >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
the forum, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >
MONDAY : 
https://www.cplusplus.com/reference/string/string/find/
https://www.cplusplus.com/reference/string/string/npos/
https://www.cs.rpi.edu/academics/courses/fall21/csci1200/lectures/02_classes_I.pdf
https://www.cs.rpi.edu/academics/courses/fall21/csci1200/lectures/03_classes_II.pdf
TUESDAY:
WED:
https://stackoverflow.com/questions/2506909/c-error-expected-initializer-before-token
https://stackoverflow.com/questions/12579658/error-expected-initializer-before-std
https://stackoverflow.com/questions/60989263/error-invalid-conversion-from-gnu-cxx-alloc-traitsstdallocatorchar
https://stackoverflow.com/questions/2263681/c-compile-error-iso-c-forbids-comparison-between-pointer-and-integer
https://stackoverflow.com/questions/2263681/c-compile-error-iso-c-forbids-comparison-between-pointer-and-integer
https://www.cplusplus.com/reference/string/string/pop_back/
https://askubuntu.com/questions/150616/ctrlc-does-not-quit-a-running-program-in-terminal#:~:text=Use%20Ctrl%20%2B%20Break%20key%20combo,return%20you%20the%20command%20prompt.
http://www.cplusplus.com/reference/valarray/slice/
https://www.w3schools.com/cpp/cpp_switch.asp
https://levelup.gitconnected.com/learning-c-working-with-text-files-91104a8fab33
http://www.cplusplus.com/forum/beginner/185610/
https://stackoverflow.com/questions/3081815/c-errors-while-compiling
https://www.softwaretestinghelp.com/cpp-errors/
https://stackoverflow.com/questions/5966698/error-use-of-deleted-function
https://stackoverflow.com/questions/18565167/non-const-lvalue-references
THURS:
https://www.cplusplus.com/doc/tutorial/files/
https://stackoverflow.com/questions/13032214/aligning-output-of-ofstream
https://stackoverflow.com/questions/7897163/stdcout-to-print-character-n-times
http://www.cplusplus.com/forum/general/256212/
https://www.geeksforgeeks.org/std-find-in-cpp/
https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
https://www.cplusplus.com/reference/vector/vector/push_back/
https://stackoverflow.com/questions/38743746/error-passing-const-string-aka-const-std-cxx11basic-stringchar-as-t/38743828
https://en.cppreference.com/w/cpp/language/ascii
FRI:
Office Hour - 4PM FOLSOM.


Remember: Your implementation for this assignment must be done on your
own, as described in "Collaboration Policy and Academic Integrity".

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 24 hours >
MONDAY:		  2 HOURS
TUESDAY:	 30 Min
WEDNESDAY:	  7 HOURS
THURSDAY:	 11 HOURS
FRIDAY:		  4 HOURS

DESCRIPTION OF CUSTOM STATISTIC:
Well-written 100-200 word description.
Taken from https://en.wikipedia.org/wiki/Letter_frequency, relative_frequency.txt 
contains the relative frequencies of each letter in text. custom_stats() calculates the 
frequency of each letter as a how often is in the seven game letters. Lastly,
it compares as a percent error between given relative_frequency and calculated relative
frequency for each letter. The output is then formatted and overrall error is printed
at the bottom.

RESULTS FROM CUSTOM STATISTIC:
Paste in a small amount of sample output into this file, or list the
file names of sample input & output included with your submisssion.
Describe what is interesting about your statistic on this data.
Please be concise!

It seems that the producers of spelling bee have a favorite set of words,
as certain letters are trending towards their real relative frequencies, while
others are quite uncommon or even too common.

letter   frequency   calc. frequency   % error
----------------------------------------------
a            0.082          0.085456   4.21411
b          0.01500           0.03056 103.73515
c          0.02800           0.05207  85.94874
d          0.04300           0.03848  10.50394
e          0.13000           0.06735  48.19555
f          0.02200           0.01924  12.53794
g          0.02000           0.04018 100.90549
h          0.06100           0.03848  36.91261
i          0.07000           0.08885  26.93023
j          0.00150           0.00566 277.28732
k          0.00770           0.01415  83.74381
l          0.04000           0.07923  98.07583
m          0.02400           0.03905  62.70514
n          0.06700           0.08319  24.16693
o          0.07500           0.07866   4.88586
p          0.01900           0.03226  69.77929
q          0.00095           0.00057  40.42832
r          0.06000           0.03396  43.40690
s          0.06300           0.00000 100.00000
t          0.09100           0.07074  22.26223
u          0.02800           0.03226  15.20737
v          0.00980           0.01188  21.27091
w          0.02400           0.01302  45.76495
x          0.00150           0.00736 390.47351
y          0.02000           0.03735  86.75723
z          0.00000           0.00000   0.00000
Total Error: 1816.09912%

August_2021.txt
letter   frequency   calc. frequency   % error
----------------------------------------------
a            0.082          0.084507   3.05736
b          0.01500           0.02817  87.79343
c          0.02800           0.03286  17.37088
d          0.04300           0.04695   9.18223
e          0.13000           0.07512  42.21740
f          0.02200           0.02347   6.70082
g          0.02000           0.03286  64.31924
h          0.06100           0.03756  38.42838
i          0.07000           0.10329  47.55198
j          0.00150           0.00000 100.00000
k          0.00770           0.00469  39.02811
l          0.04000           0.09390 134.74179
m          0.02400           0.04695  95.61816
n          0.06700           0.08920  33.13712
o          0.07500           0.07981   6.41627
p          0.01900           0.01878   1.16135
q          0.00095           0.00000 100.00000
r          0.06000           0.03286  45.22692
s          0.06300           0.00000 100.00000
t          0.09100           0.06573  27.77176
u          0.02800           0.02347  16.16365
v          0.00980           0.01878  91.62595
w          0.02400           0.00939  60.87637
x          0.00150           0.00939 525.97809
y          0.02000           0.04225 111.26760
z          0.00000           0.00000   0.00000
Total Error: 1805.63477%

2020.txt
letter   frequency   calc. frequency   % error
----------------------------------------------
a            0.082          0.082778   0.94824
b          0.01500           0.03492 132.77101
c          0.02800           0.05492  96.15535
d          0.04300           0.04512   4.92030
e          0.13000           0.04394  66.20093
f          0.02200           0.02393   8.77706
g          0.02000           0.03452  72.61671
h          0.06100           0.04629  24.11039
i          0.07000           0.06709   4.16410
j          0.00150           0.00314 109.23237
k          0.00770           0.01883 144.55733
l          0.04000           0.07768  94.19380
m          0.02400           0.03845  60.19353
n          0.06700           0.07022   4.81136
o          0.07500           0.07297   2.70694
p          0.01900           0.03413  79.63702
q          0.00095           0.00039  58.70414
r          0.06000           0.05139  14.34549
s          0.06300           0.00000 100.00000
t          0.09100           0.07101  21.96897
u          0.02800           0.03923  40.11096
v          0.00980           0.01491  52.12048
w          0.02400           0.01922  19.90323
x          0.00150           0.00667 344.61877
y          0.02000           0.04825 141.27109
z          0.00000           0.00000   0.00000
Total Error: 1699.03967%



MISC. COMMENTS TO GRADER:  
I have commented out a large portion of custom_stats, as it requires
my provided .txt file for parsing, so if you would like to test it,
please comment my temporary section, and uncomment the main code.

Thank You!


