def parse_line(line):
    if line.count("/") >= 3:
        temp_split = line.split("/")
        print(temp_split)
       # print("if statement passed (flag .5)")
        try:
            last_three_integers = (int(temp_split[-3]),int(temp_split[-2]),int(temp_split[-1])) #lots of tuples and lists initialized, messy but works
         #   print("Flag 1")
            remaining_strings = list(temp_split[i] for i in range(0,len(temp_split)-3)) #wanted to messed around with generator objects
         #   print("Flag 2")
            print(remaining_strings)
         #   print("Flag 3")
            s = ""
            for j in range(len(remaining_strings)):
                s += remaining_strings[j]
            print(s)
         #   print("Flag 4")
            return (last_three_integers[0],last_three_integers[1],last_three_integers[2],s)
        except:
            return None
    #print("If statement failed (flag 0)")
    return None
    
if __name__ == "__main__":
    print(parse_line(" Again some spaces\n/12/12/12"))