""" 
    This is the skeleton to demonstrate how to put Lab 10 together. 
    It provides an example to show the use of doctest. Note the function,
    addone(x) presented below has an additional 4 lines after 
    the normal function description. The lines beginning with '>>>'
    indicate examples of how the function can be called, and 
    the lines immediately after represent the expected return
    from the call. So, for example, 'addone(1)' should return '2'
    and 'addone(0) should return 1. These lines provide examples
    for a potential user of the lab10 module, but more importantly
    for this lab, they work with the doctest module to allow us to
    do automated testing. 
    
    Look at the file 'test_driver.py' for an example of how to use
    this testing information. Then come back here and change 
    the answer for one or both of the addone examples to 
    an incorrect value and run the testing again to see how a failing
    test is reported.
"""

def closest1(values): #This seems really bad, this will be a n**n time program yuck. ends up with a lot of duplicates yikers
    """
    closest1 returns the two closest values in values
    #Generic always increasing set
    >>> closest1( [1,2,4,8,16,32,])
    (1, 2)
    
    #Same Values Check
    >>> closest1([1,17,123,-4,-4,18])
    (-4, -4)
    
    #Two cases of same values, since min() is used, technically (1,1) is a "smaller" value
    >>> closest1([1,1,123,654,423,123])
    (1, 1)
   
    
    """
    differences = []
    for i in range(len(values)):
        for j in range(len(values)):
            if i != j:
                differences.append( (abs(values[i]-values[j]), values[i], values[j]) )
    ind = differences.index(min(differences))
    return ( differences[ind][1],differences[ind][2])
    
if __name__ == "__main__":
    print(closest1( [1,2,4,8,16,32,]))
    print(closest1( [1,17,123,-4,-4,18]))
    print(closest1( [1,1,123,654,423,123]))
    print(closest1([ 15.1, -12.1, 5.4, 11.8, 17.4, 4.3, 6.9 ]))