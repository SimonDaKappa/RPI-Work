
"""
Lecure 11 Exercise 1, determine if the first passed semester was before the second passed on
tuples in form tuple[0] = "Spring/Fall"(str) , tuple[1] = Year(int)
= """

def earlier_semester(semester_1,semester_2):
    """determines if the first passed semester was before the second passed on"""
    if semester_1[1] < semester_2[1]:
        return True
    elif semester_1[1] > semester_2[1]:
        return False
    else:
        if semester_1[0] == "Spring" and semester_2[0] == 'Fall':
            return True
        elif semester_1[0] == "Fall" and semester_2[0] == 'Spring':
            return False
        elif semester_1[0] == semester_2[0]:
            return False
        else:
            return -1
        
w1 = ('Spring',2015)
w2 = ('Spring',2014)
w3 = ('Fall', 2014)
w4 = ('Fall', 2015)
print( "{} earlier than {}? {}".format( w1, w2, earlier_semester(w1,w2)))
print( "{} earlier than {}? {}".format( w1, w1, earlier_semester(w1,w1)))
print( "{} earlier than {}? {}".format( w1, w4, earlier_semester(w1,w4)))
print( "{} earlier than {}? {}".format( w4, w1, earlier_semester(w4,w1)))
print( "{} earlier than {}? {}".format( w3, w4, earlier_semester(w3,w4)))
print( "{} earlier than {}? {}".format( w1, w3, earlier_semester(w1,w3)))