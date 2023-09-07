<Simon Gibson>
<Lab 3>

Notes:

Errors:
1. Lack of include guards in header files. -> Deleted extra include in line.cpp
2. Forgot to include <algorithm> -> included algorithm

Warnings: 
1. Assumptions that basic types intialize to a default value
   when declared. -> Caused some sort of garbage memory as int value
2. Lack of return statement in compute_slope, default return;
3.  roads local reference, deleted ampersand
4. * -1 -> *= -1
5. For loop, mismatch of type -> long unsigned