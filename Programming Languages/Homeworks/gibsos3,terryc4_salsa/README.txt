Simon Gibson, Curtis Terry - PA 2
The implementation is as :

Create worker i for partition i
Read partitions i data into worker i, as well as a reference ot every other worker
Perform Part A entirely within worker i
Perform Part B by messaging every other worker for the required node degree and join, using a : waitfor(token) 
statement to prevent race conditions

For distributed computing: 
Workers are assigned to a theater round-robin such as worker[i] in theater( i % numTheaters)


As salsa does not support generic types, I have two auxilliary types:
ArrayList_I is a wrapper of ArrayList<Integer>
ArrayList_S is a wrapper of ArrayList<String>

The file Helper.java mainly contains functions for ease of use with standard <type>[] arrays
such as contains(), findIndex(), or printArr()

I do not know why, but if you create a custom class with calculation intensive methods, there is a chance that 
salsa simply ignores which worker instantiated and owns the class instance, and will
pass the data around willy nilly to other workers. I did not find this out until the end of part B and had to delete
the entire class and restart the assignment.

BUGS: 
None that I could find