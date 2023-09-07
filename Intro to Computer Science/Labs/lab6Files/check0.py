"""LAB 6: Checkpoint 0 - Simon Gibson"""

def printnumline(number):
    """Prints all natural numbers from 0 to number (inclusive)"""
    line = ""
    for num in range(0,number + 1):
        line+=   str(num) + " "
    return line

def generatepairsstring(minrow, maxrow, mincol, maxcol):
    """Generates pairs which loop from 0,0 to number,number in base_number"""
    c_h = c_v = 0
    line = ""
    for row in range(minrow,maxrow+ 1):
        c_h = 0
        for col in range(mincol,maxcol + 1):
            line += str(row) + "," + str(col) + " "
            c_h += 1
            if c_h == maxcol + 1: 
                line += "\n"
            elif c_h % 3 == 0:
                line += " "
        c_v += 1
        if c_v % 3 == 0 and c_v < maxrow:
            line+= "\n"
    return line
    
def generaterow(row, mincol,maxcol, line = ""):
    c_h = 0
    for col in range(mincol,maxcol):
        line += str(row) + "," + str(col) + " "
        c_h +=1
        if c_h % 3 == 0:
            line += " "
    return line

def generatecol_vertical(col, minrow,maxrow, line = ""):
    for row in range(minrow,maxrow + 1):
        line += str(row) + "," + str(col) + "\n"
    return line

def generatecol_horizontal(col, minrow,maxrow, line = ""):
    for row in range(minrow,maxrow + 1):
        line += str(row) + "," + str(col) + " "
    return line

def formatbigthing(minrow,maxrow,mincol,maxcol, line = " "):
    """ THINKING: Assuming (maxrow - minrow) == (maxcol - mincol) if we have n rows and n cols, split up into in (n//3)^2 sub groups, every three counts add a \n between subgroups, everysubgroup count % 3 != 0 add a space 
    """    
    # After thinking this would be impossible, i would have to track indices  to insert spaces, stupid way to do this
    
 



if __name__ == "__main__":
    #Test Cases
    print(printnumline(8))
    print(generatepairsstring(0,8,0,8))
    print(generatepairsstring(2,2,0,8))
    print(generatepairsstring(0,8,5,5)) # Makes the 3x3 with wrong indices wack
    print(generaterow(2,0,8))
    print(generatecol_vertical(5,0,8))
    print(generatecol_horizontal(5,0,8))
    #I can just use my generatepairsstring() function to do the subgroup for nwo
    print(generatepairsstring(0,2,0,2))