import hw5_util

""" LINEAR APPROXIMATION OF GRADIENT ASCENT 

Important Assumptions:
    
    1. rows >= 2
    2. col >=2 and all rows have same length (number of columns)
    3. Heights are positive integers
    4. Start locations are valid
    5. path locations are all within range of rows and columns of grid
    
Attack:
   1. Find global max
   2. Find path from start to global max  *1
        


Pathing:
    Instead of taking the gradient at any one point, compare the linear slopes at the 4 cardinal directions from start point


*:
    1. Seems a little cheaty mathematically, but if we know position of global max, and get stuck at local max:
        1. Find direction to 



""" 