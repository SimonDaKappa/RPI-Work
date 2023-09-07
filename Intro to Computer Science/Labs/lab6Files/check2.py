""" Lab 6 Check2: Simon Gibson

Steps : takes board "bd", does wizardry to check if inputted number at (row,col) is valid, if so, updates board and calls checkpoint1 board print function
""" 
import check1

def ok_to_add(value,row,col,board,blocksize = 3):
    if value <= 9 and value > 0:
        if row < len(board) and col < len(board[row]):
            for val_inrow in board[row]:
                if val_inrow == value:
                    print("This number cannot be added")
                    return False
            transposed = list(zip(*board))
            for x in range(len(transposed[col])): #row_ is actually a column of board
                if str(value) == transposed[col][x]:
                    print("This number cannot be added")
                    return False
            if check_subgroup(value, row, col, board) == False:
                print("This number cannot be added")
                return False
            if board[row][col ] != ".":
                print("This number cannot be added")
                return False
        else:
            print("This number cannot be added")
            return False
    else:
        print("This number cannot be added")
        return False
    
    board[row][col] = value
    check1.printboard(board)
    return True

def check_subgroup(value, row, col, board,blocksize = 3):
    "Loops over lower and upper bounds of subgroup to check if the subgroup contains the value"
    subg = find_subgroup(row,col)
    for row_i in range(subg[0]*blocksize, subg[0] * blocksize  + blocksize  ): #range() is non-inclusive so even though its range(6,9) 6-8 are looped
        for col_i in range(subg[1]*blocksize, subg[1] * blocksize  + blocksize):
            if board[row_i][col_i] == str(value): #cast to str for if statement to work
                return False
    return True

def find_subgroup(row,col,blocksize = 3):
    """Uses integer division to find subgroup number, returns as tuple"""
    rowsubg = row // blocksize
    colsubg = col // blocksize
    return (rowsubg,colsubg)    
                

if __name__ == "__main__":
    bd = [ [ '1', '.', '.', '.', '2', '.', '.', '3', '7'],
           [ '.', '6', '.', '.', '.', '5', '1', '4', '.'],
           [ '.', '5', '.', '.', '.', '.', '.', '2', '9'],
           [ '.', '.', '.', '9', '.', '.', '4', '.', '.'],
           [ '.', '.', '4', '1', '.', '3', '7', '.', '.'],
           [ '.', '.', '1', '.', '.', '4', '.', '.', '.'],
           [ '4', '3', '.', '.', '.', '.', '.', '1', '.'],
           [ '.', '1', '7', '5', '.', '.', '.', '8', '.'],
           [ '2', '8', '.', '.', '4', '.', '.', '.', '6'] ]
    
    val = 4
    r = 0
    c = 1
    print("Test value used is val=",val,"row =",r,"column=",c)
    ok_to_add(val, r, c, bd)
    #print(find_subgroup(r,c)) #Testing errors with check_subgroup
    #print(check_subgroup(val,r,c,bd)) #Testing errors with check_subgroup
    #check1.printboard(bd) just tested this to see if bd actually keeps values assigned