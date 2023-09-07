""" Lab 6 Check3: Simon Gibson

Steps : Adds onto check2
""" 
import check1
import lab06_util

def verify_board():
    board = get_board()
    check1.printboard(board)
    for row in range(len(board)):
        for col in range(len(board[row])):
            #print("row =",row,"col =",col,"val=",board[row][col]) #Test stuff
            if ok_to_add(board[row][col],row,col,board) == False:
                print("Solution is not valid")
                return False
    print("Solution is valid")
    return True
    
    
    
    
def get_board():
    return lab06_util.read_sudoku(input("Please enter a file name ==> "))

def ok_to_add(value,row,col,board,blocksize = 3):
    if value == ".":
        print("Cannot add '.'")
        return False
    value = int(value)
    #print("Casted",value) Test
    if value <= 9 and value > 0:
        #print("passed 1")
        if row < len(board) and col < len(board[row]):
            #print("passed 2")
            for val_inrow in board[row]:
                if val_inrow == value:
                    print("This number cannot be added")
                    return False
            #print("passed 3")
            transposed = list(zip(*board))
            for x in range(len(transposed[col])): #row_ is actually a column of board
                if str(value) == transposed[col][x] and x != row:
                    print("This number cannot be added")
                    return False
            #print("passed 4")
            if check_subgroup(value, row, col, board) == False:
                print("This number cannot be added")
                return False
            #print("passed 5")
        else:
            print("This number cannot be added")
            return False
    else:
        print("This number cannot be added")
        return False
    #print("passed 6")
    board[row][col] = value
    #check1.printboard(board)
    return True

def check_subgroup(value, row, col, board,blocksize = 3):
    "Loops over lower and upper bounds of subgroup to check if the subgroup contains the value"
    subg = find_subgroup(row,col)
    for row_i in range(subg[0]*blocksize, subg[0] * blocksize  + blocksize  ): #range() is non-inclusive so even though its range(6,9) 6-8 are looped
        for col_i in range(subg[1]*blocksize, subg[1] * blocksize  + blocksize):
            if board[row_i][col_i] == str(value) and (row_i,col_i) != (row,col): #cast to str for if statement to work
                return False
    return True

def find_subgroup(row,col,blocksize = 3):
    """Uses integer division to find subgroup number, returns as tuple"""
    rowsubg = row // blocksize
    colsubg = col // blocksize
    return (rowsubg,colsubg)    
                

if __name__ == "__main__":
    verify_board()

