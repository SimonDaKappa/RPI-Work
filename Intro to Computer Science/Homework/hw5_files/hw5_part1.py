""" HW5: Simon Gibson 
    IMPORTANT NOTE TO SELF: when writing a function ALWAYS put grid and grid_number in order func(grid,grid_number), or have fun trying to fix that again. same with grid and n, func(grid,n).  I think n == grid_number
    but im too lazy to change it on all my code.

"""
import hw5_util

def bruh():
    """IDK I just like having everything in functions and my main method being one line."""
    grid = askgrid() #grid[0] is the nested list of positions, grid[1] is the grid number
    choices(grid[0],grid[1])
    startpoints = startpointmath(grid[0],grid[1]) #made these variables with returns incase I need them later
    path_bool = pathing(grid[0],grid[1]) # same case as startpoints above ^
    
    
    
def askgrid():
    while(True):
        n = int(input("Enter a grid index less than or equal to " + str(hw5_util.num_grids()) + " (0 to end): ")) 
        print(n)
        if n >= 1 and  n <= hw5_util.num_grids():
            return (hw5_util.get_grid(n),n)
        
def choices(grid,n):
    """Asks whether the user wants to rpint the grid, if yes calls gridprint()"""
    choice = input("Should the grid be printed (Y or N): ")
    print(choice)
    if choice.lower() == "y":
        gridprint(grid,n,1)
        #print(grid)
    else:
        gridprint(grid,n,0)
        
def gridprint(grid,n,c):
    """Prints grid in readable form"""
    if c == 1:
        print("Grid",n)
        
        for row in range(0,len(grid)):
            for col in range(0,len(grid[row])):
                print("{:>4}".format(grid[row][col]),sep='',end = "")
            print()
    print("Grid has",len(grid),"rows and",len(grid[0]),"columns")  

def get_nbrs(grid,pos):
    """pos is a tuple of form (row,col). Finds all neighbors of pos within valid bounds of grid. Returns a list of tuples of valid neighboring positions"""
    neighbors = []
    if pos[0] - 1 >= 0:
        neighbors.append((pos[0]-1,pos[1]))
    if pos[1] - 1 >= 0:
        neighbors.append((pos[0],pos[1] -1))
    if pos[1] + 1 <= len(grid[0]) - 1:
        neighbors.append((pos[0],pos[1]+1))
    if pos[0] + 1 <= len(grid) - 1:
        neighbors.append((pos[0]+1,pos[1]))
    return neighbors

def print_nbrs(pos,neighbors):
    """Prints out the neighbors of a position formatted"""
    print("Neighbors of ",pos,":",sep='',end='')
    for nbr_pos in neighbors:
        print("",nbr_pos,end="")
    print()    
        
def startpointmath(grid,grid_number):
    """Finds the start points for a grid and calls print_nbrs for each, returns the start positions"""
    starts = hw5_util.get_start_locations(grid_number)
    for start_pos in starts:
        print_nbrs(start_pos,get_nbrs(grid,start_pos))
    return starts

def pathing(grid,grid_number):
    """Determines if the given pathing is valid, Ie: each point is a neighbor of the previous. Code is ugly but I'll comment later today"""
    
    path  = hw5_util.get_path(grid_number)
    
    for pos_index in range(len(path)-1):
       c=0
       neighbors = get_nbrs(grid,path[pos_index])
       for nbr in neighbors:
           if path[pos_index+1] == nbr:
               c+=1
       if c == 0:
           print("Path: invalid step from",path[pos_index],"to",path[pos_index+1])
           return False
    print("Valid path")
    
    up_c = down_c = 0
    for pos_index in range(len(path)-1):
        tempc = grid[path[pos_index+1][0]][path[pos_index+1][1]] - grid[path[pos_index][0]][path[pos_index][1]]
        if tempc > 0:
            up_c += tempc
        elif tempc < 0:
            down_c += tempc
        
    print("Downward",-1*down_c)
    print("Upward",up_c)
    return True
   
 

if __name__ == "__main__":
    bruh()



