def start_game():
    turns = int(input("How many turns? => "))
    print(turns)
    name  = input("What is the name of your pikachu? => ")
    print(name)
    occasion =  int(input("How often do we see a Pokemon (turns)? => "))
    print(occasion)
    print("\nStarting simulation, turn 0",name,"at (75, 75)")
    runtime(turns,name,occasion)
    
def runtime(turns,name,occasion):
    turn_number = 0
    record  = [] 
    pos = [75,75]
    while turn_number < turns:
        temp  = 0
        direction = ""
        while(temp < occasion):
           direction = input("What direction does " + name + " walk? => ")
           print(direction)
           direction = direction.upper()
           if(direction == "N" or direction == "E" or direction == "S" or direction == "W"):
                pos = move_pokemon(direction,pos,5)
           temp+=1
           turn_number +=1
        temp = 0
        print("Turn ",turn_number,", ",name," at (",pos[0],", ",pos[1],")",sep='')
        poketype = input("What type of pokemon do you meet (W)ater, (G)round? => ")
        print(poketype,end='\r\n')
        poketype = poketype.upper()
        if poketype == "G":
            if direction == "N" :
                direction = "S" 
            elif direction == "W":
                direction = "E"
            elif direction == "S":
                direction = "N"
            elif direction == "E":
                direction = "W"
            pos = move_pokemon(direction,pos,10)
            print(name," runs away to (",pos[0],", ",pos[1],")",sep='')
            record.append("Lose")
        elif poketype == "W":
            pos= move_pokemon(direction,pos,1)
            print(name," wins and moves to (",pos[0],", ",pos[1],")",sep='')
            record.append("Win")
        else:
            record.append("No Pokemon")
    print(name," ends up at (",pos[0],", ",pos[1],"), Record: ",record,sep='') 
         
def move_pokemon(direction,pos,steps):
    if direction == "N":
        pos[0] = max(0, pos[0]-steps)  
    if direction == "W":
        pos[1] = max(0, pos[1]-steps)
    if direction == "S": 
        pos[0] = min(150, pos[0]+steps)
    if direction == "E":
        pos[1] = min(150, pos[1]+steps)
    return pos

start_game()