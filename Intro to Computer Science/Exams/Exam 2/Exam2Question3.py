"""
Simon Gibson - Exam 2 Question 3 - Truth Tables
"""
#import evaluate
def triple_bool(bool1,bool2,bool3): #made this just so the red dot dissapears
    return (bool1 and bool2) or bool3 #For testing 

def truth_table(): # I need to create nested loops that go over all permutations of 3 T/F Booleans, oof.
    bools = [True,True,True] 
    t_t = []
    c = 2
    c_end = 2

    for i in range(8):
        t_t.append( (bools[0],bools[1],bools[2], triple_bool(bools[0],bools[1],bools[2]) ))
        #print(t_t)
        if i < 4:
            if c == 0:
                c = 2
                bools[2] = False
            if c == 1:
                bools[2] = True
            if i == 3:
                bools[0] = False
                bools[1] = True
                bools[2] = True
                continue
            bools[c] = False
            c-=1
        else: 
            bools[c_end] = False
            if c_end == 1:
                bools[2] = True
            if c_end == 0:
                c_end = 2
                bools[2] = False
            c_end -=1
    print_truth_table(t_t)

        
    
def print_truth_table(t_t):
    print("bool1\tbool2\tbool3\tResult")
    print("----\t----\t----\t----")
    for i in range(len(t_t)):
        print("{:<8}{:<8}{:<8}{:<8}".format(str(t_t[i][0]),str(t_t[i][1]),str(t_t[i][2]),str(t_t[i][3])))
 
if __name__ == "__main__":
    truth_table()
    