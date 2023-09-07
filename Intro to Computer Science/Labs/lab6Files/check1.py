def printboard(board, output = ""):
    """THINKING:  to print the "|" we probably need to check if the column index is 0 or len(board[row]) and if so output += " | \
    # ------------------------- 9x9 with 25 "-" , possible formula: "-" * (len(board[0])*3) -2 or "-" * (len(board[0])*2) + 7 """
    output += "-" * ((len(board[0])*3) -2) + "\n"
    for row in range(0,len(board)):
        for col in range(0,len(board[row])):
            
            if col == 0:
                output += '|'
            
            if (( col ) % 3 == 0) and col != 0:
                output += " |"
            
            output += " " + str(board[row][col])
            
            if col == len(board[row]) - 1 :
                output += " |\n"
        
        if (row + 1) % 3 == 0:
            output += "-" * ((len(board[0])*3) -2) + "\n"
    print( output )
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
    
    print(len(bd))
    print(len(bd[0]))
    print(bd[0][0])
    print(bd[8][8])
    
    printboard(bd)