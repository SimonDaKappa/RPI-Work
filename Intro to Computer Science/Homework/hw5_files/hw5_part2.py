""" HW5: Simon Gibson 
    IMPORTANT NOTE TO SELF: when writing a function ALWAYS put grid and grid_number in order func(grid,grid_number), or have fun trying to fix that again. same with grid and n, func(grid,n).  I think n == grid_number
    but im too lazy to change it on all my code. *Copied from part1
    
    Part2 Steps: Goal = try to reuse as much of part1 as possible while optimizing it
        1. Call askgrid() and assign to grid , is a tuple (grid,gridnumber)
        2. Call global_max() and assign to globalmax 
        3. Need new pathing function     (1)
        4. new path printing function    (2)
        5. Figure out path grid function (3)
        
    (1) Pathing:
        Requirements:
            cant step up higher than user input step_max
            cant step down or step "0" (No incline)
            if multiple neighbors have same elevation, go in direction of neighbor which comes earlier in list: Ideally do without If statement, but no biggy if I end up using one <- At least this happened automatically and i could forget ab it
            
            ^ lol  I wrote this freshbrained and thinking it wouldnt take 7 complete rewrites of part two. What a nerd
    (3) Grid Path:
        Requirements: For each position find the total number of paths that include it        
            

"""
import hw5_util

def bruh(): #For future: Don't call main function start():, creates a while loop.
    """IDK I just like having everything in functions and my main method being one line."""
    
    grid = askgrid() #grid[0] is the nested list of positions, grid[1] is the grid number
    step = int(input("Enter the maximum step height: "))
    print(step)
    ch = choices(grid[0])
    globalmax = global_max(grid[0])
    startpointmath(grid[0],grid[1],globalmax[0],step,ch)

def choices(grid):
    """Determines whether the user wants to print the path grid, if yes, returns True"""
    
    choice = input("Should the path grid be printed (Y or N): ")
    print(choice)
    print("Grid has",len(grid),"rows and",len(grid[0]),"columns")
    if choice.lower() == "y":
        return True
    return False  

def startpointmath(grid, grid_number, globalmax, step, ch ):
    """Finds the start points for grid 'grid_number' and calls steeppath() and gradualpath() for all"""
    starts = hw5_util.get_start_locations(grid_number)
    global path_list 
    path_list = []
    for startpoint in starts: #calls both pathing for each given startpoint
        steeppath(grid,grid_number,startpoint,globalmax,step,path = [startpoint])
        gradualpath(grid,grid_number,startpoint,globalmax,step,path = [startpoint])
    print("===") #This is not ideal, but I ran out of time to retrace the code and put it in proper place, works fo rnow
    if ch == True: #also not ideal, didnt work when called in choices() b/c choices is called b4 startpointmath()
        printpath_list(grid)

def printpath_list(grid, c = 0 ): #Tommorrow Morning Fix this, this doesnt work. Disregard previous statement I fixed it.
    """
    Takes a list of all paths from start locations and creates a  new grid of the number of paths that transverse over each point in chosen grid. Prints out formatted new grid
    """    
    gridcounter = [[0]*len(grid[0]) for i in range(len(grid))] # Need to remember this for future. creating a list = [[x]*integer1]*integer2 creates integer1  copies of the inner list, any changes to one inner list reflects on all inner lists.
    print("Path grid")
    for i in range(len(path_list)): 
        for j in range(len(path_list[i])):
            gridcounter [path_list[i][j][0]][path_list[i][j][1]] += 1# [Row coordinate of tuple in path_list][Col coordinate of tuple in path_list] -> Coordinates of tuple in path list = path_list[i][j]
    
    for row in gridcounter: #Formatting the gridcounter output into a grid
        for col in row:
            if c < len(grid[0]):
                if col == 0:
                    print("  .",end= '')
                    c+=1
                else:
                    print(" ",col,end= '')
                    c+=1
            else:
                print()
                if col == 0:
                    print("  .",end='')
                    c = 1
                else:
                    print(" ",col,end='')
                    c = 1
            
def askgrid():
        grid_number = int(input("Enter a grid index less than or equal to " + str(hw5_util.num_grids()) + " (0 to end): ")) 
        print(grid_number)
        if grid_number >= 1 and  grid_number <= hw5_util.num_grids():
            return ( hw5_util.get_grid(grid_number), grid_number )
    
def global_max(grid, maxh = 0, maxh_pos = (None,None), temph = 0 ):
    """Finds and returns the global maximum and position of global max"""
    for row in range(len(grid)):
        for col in range(len(grid[row])):
            temph = maxh
            maxh = max(maxh, grid[row][col])
            if maxh > temph:
                maxh_pos = (row,col)
    print("global max:",maxh_pos,maxh)
    return ( maxh, maxh_pos )
                          
def steeppath(grid, grid_number, pos, globalmax, step, path):
    """
    Calls get_nbrs() to find the valid neighbors for pos. Loops over the neighbors and categorizes them into "valid, negative, or too steep"
    Uses this categorization to recursively call until one of the three conditions for "global, local, or none" is met
    if condition is met it calls printpathing()
    When finding conditions it calls the max() of valid moves
    Note: Path_list is global variable, so that it can be iterated over all start points and their recursions
    """
    nbrs = get_nbrs(grid,pos)
    neg = 0 #negativel slope counter
    toosteep = 0 #too high elevation change counter
    p_h = []#Lists of neighbors with positive slops and their positions
    p_pos = [] 
    for nbr in nbrs: #nbr is a tuple containing position info in neighbors,#loops over valid neighbors
        #print(nbr)
        nbrh = grid[nbr[0]][nbr[1]]
        #print(nbrh)
        posh = grid[pos[0]][pos[1]]
        dif = nbrh - posh 
        #Categorizing each neighbor based on its height
        if dif <= 0:
            neg+=1
        elif dif <= step:
            p_h.append(nbrh)
            p_pos.append(nbr)
        elif dif > step:
            toosteep += 1
    
    if neg == len(nbrs): # checks: the recursion will only break when the path reachs a max,plateau, or surrounded by sides too steep. Calls printpathing()
        if grid[pos[0]][pos[1]] == globalmax:
            print("===\nsteepest path")
            printpathing(path)
            print("\nglobal maximum")
            path_list.append(path)
            return 
        else:
            print("===\nsteepest path")
            printpathing(path)
            print("\nlocal maximum")
            path_list.append(path)
            return 
    if toosteep + neg == len(nbrs):
        print("===\nsteepest path")
        printpathing(path)
        print("\nno maximum")
        path_list.append(path)
        return 
    
    x = max(p_h) #Setup for calling recursion of function
    y = p_h.index(x)
    path.append(p_pos[y])
    pos = p_pos[y]
    steeppath(grid, grid_number, pos, globalmax, step, path)

def gradualpath(grid, grid_number, pos, globalmax, step, path):
    """
    Calls get_nbrs() to find the valid neighbors for pos. Loops over the neighbors and categorizes them into "valid, negative, or too steep"
    Uses this categorization to recursively call until one of the three conditions for "global, local, or none" is met
    if condition is met it calls printpathing()
    When finding conditions it calls the min() of valid moves
    Note: Path_list is global variable, so that it can be iterated over all start points and their recursions
    """
    nbrs = get_nbrs(grid,pos)
    neg = toosteep = 0
    p_h = []
    p_pos = []
    for nbr in nbrs: #loops over valid neighbors,#nbr is a tuple containing position info in neighbors
        #print(nbr)
        nbrh = grid[nbr[0]][nbr[1]]
        #print(nbrh)
        posh = grid[pos[0]][pos[1]]
        dif = nbrh - posh
        #Categorizing each neighbor based on its height
        if dif <= 0:
            neg+=1
        elif dif <= step:
            p_h.append(nbrh)
            p_pos.append(nbr)
        elif dif > step:
            toosteep += 1
        
    if neg == len(nbrs): #checks: the recursion will only break when the path reachs a max,plateau, or surrounded by sides too steep. Calls printpathing()
        if grid[pos[0]][pos[1]] == globalmax:
            print("...\nmost gradual path")
            printpathing(path)
            print("\nglobal maximum")
            path_list.append(path)
            return 
        else:
            print("...\nmost gradual path")
            printpathing(path)
            print("\nlocal maximum")
            path_list.append(path)
            return 
    if toosteep + neg == len(nbrs):
        print("...\nmost gradual path")
        printpathing(path)
        print("\nno maximum")
        path_list.append(path)
        return
    
    x = min(p_h) #Setup for calling recursion of function
    y = p_h.index(x)
    path.append(p_pos[y])
    pos = p_pos[y]
    gradualpath(grid, grid_number, pos, globalmax, step, path)

def printpathing(path):
    """Formats path output"""
    c = 0
    for spot in path:
        if c < 5:
            print(spot,end= ' ')
            c+=1
        else:
            print()
            print(spot,end=' ')
            c = 1

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
          
def find_max_step():
    max_step = int(input("Enter the maximum step height: "))
    print(max_step)
    return max_step

if __name__ == "__main__":
    bruh() #originally was called start(), but start() as a main function is a infinite loop lol, renamed it to fit my mood when finding this out.
