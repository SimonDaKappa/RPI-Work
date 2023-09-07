HOMEWORK 7: HALLOWEEN COSTUME MAPS


NAME:  < Simon Gibson >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
the forum, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

https://www.cplusplus.com/reference/utility/pair/pair/
https://www.delftstack.com/howto/cpp/vector-pair-in-cpp/
http://www.cplusplus.com/forum/beginner/218111/
https://github.com/DynamoRIO/drmemory/issues/1839
https://www.google.com/search?q=how+long+to+stepe+black+tea&rlz=1C1CHBF_enUS918US918&oq=how+long+to+stepe+black+tea&aqs=chrome..69i57j0i13l6j0i13i30l2j0i22i30.3257j0j7&sourceid=chrome&ie=UTF-8
https://stackoverflow.com/questions/26281979/c-loop-through-map
https://www.cplusplus.com/reference/list/list/begin/
https://stackoverflow.com/questions/15031803/c-invalid-pointer-error

Remember: Your implementation for this assignment must be done on your
own, as described in "Collaboration Policy and Academic Integrity".



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 12 HOURS >
WED : 4 HOURS
THU : 8 HOURS



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)
Let n be the number of different costumes in the shop,
m be the maximum number of copies of a given costume, and
c be the number of customers who visit the shop.

a (add):

Cases:
    New addition to shop (initial stock):
        Searches for item, doesnt find it. Map find is O(log(n))
        Constructs a pair<int, list< pair<string,string>> and creates node
        with key costume_name. The pair is constructed in constant time,
        and the list is constructed in constant time. The new key-value
        pair is placed accordingly in the tree (of the map) in O(log(n)) 
        time. Also some cout statements for formatting output ( O(1) ).
        Not dependent on max copies of costume, or number of customers
        Thus the overall time complexity is O(log(n) + 1 + 1 + log(n) + 1) 
        = O(log(n))
    
    Costume already sold by store (add stock):
        Accesses the integer value in the .first part of the pair<int,list>
        (constant time) and performs a += operation (constant time). Also
        does some cout statements for output (constant time). Not dependent 
        on max copies of costume, or number of customers.Thus the time 
        complexity is O(1 + 1 + 1) = O(1).

    Average Case: O(1)
    Worst (new) : O(log(n))

r (rent):

Cases:

    Shop does not carry costume:
        Searches for costume, doesnt find it. Worst case is O(log(n))
        Performs a cout statement and returns, both of whichb are O(1).
        Thus time complexity is O(log(n) + 1 + 1) = O(1) Not dependent 
        on max copies of costume, or number of customers.

    Shop carries costume but out of stock:
        costume_shop[costume_name] O(Logn)
        Performs a cout statement O(1) and tries to find customer, worst
        case is a new customer with complexity O(log(c)). If new customer,
        creates new people node and assigns the value to empty string. Placement
        of the new node is O(log(c)). Afterwards returns O(1). Thus in worst case,
        the time complexity is O(logn + 1 + log(c) + log(c) + 1) = 
        O(logc + logn). In best O(logn).

    In stock but first time customer:
        costume_shop[costume_name] O(Logn)
        O(logc) find statement for new customer. Creation of new people node of
        O(logc). Pushes back customers name to list of customers in costume_shop
        O(1). cout statements O(1). Time complexity of O(logn + logc + logc  + 1 + 1)
        = O(logn + logc)

    Return customer renting same costume:
        Accesses people[p] O(logc) and compares to string O(1). cout statements O(1).
        Total time complexity of O(logc + 1) = O(logc).
    
    Return customer with different costume:
        Accesses people[p] O(logc) and compares to string "" O(1). cout statements O(1).
        costume_shop[costume_name] O(Logn).
        Creates iterator O(1). loops over costume_shop costumer list until iterator points
        to customers name. Worst case of O(c). Average case of O(logc). Once found performs 
        a list erase O(1) and a list push_back O(1). Accesses people[p] O(logc) and updates
        value O(1). Total time complexity of O(logn + logc + 1 + 1+ 1 + logc + 1 + logc) 
        = O(logn + logc)
    
    Return customer with no costume:
        Accesses people[p] O(logc) and compares to "" O(1). Accesses costume_shop[costume_name]
         O(logn).List push_back O(1). cout statemens O(1). Total time complexity of O(logn + logc).


l (look up):

Cases:

    Does not carry costume:
        costume_shop.find with worst case O(logn). Comparison O(1). cout statements
        O(1). Total time complexity of O(1). 

    Carries Costume:
        basic accesses and comparisons O(1). cout statements O(1). Subcase if costume
        being rented. If rented: more basic accesses and comparisons O(1). Loops over
        all costumers renting the costume (list iterator while loop). The loop will
        iterate some fraction of the total amount of costume copies O(m/x) = O(m) where
        x is some integer > 0. Total time complexity in worst case (costume rented) of
        O(1 + 1 + 1 + m/x) = O(m).

p (print):

    Single Case:
        Performs basic accesses,cout statements, and comparisons O(1). Loops over people
        using iterator from start to end O(c). some more basic acceses, comparisons, and cout
        statements O(1). Total time complexity of O(c).




EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


