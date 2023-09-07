def check2():
    fnum = str(input("Please enter the file number ==> "))
    print(fnum)
    parno = int(input("Please enter the paragraph number ==> "))
    print(parno)
    lineno = int(input("Please enter the line number ==> "))
    print(lineno)
    fnum += ".txt"
    line = get_line(fnum,parno-1,lineno-1) #Have to subtract one because index start at 0
    return line

def get_paragraph_list(fname): #Returns a list of lists . Outer list is a paragraph, sublists are lines in the paragraph
    """
    Steps: 
        1. To find the paragraph :
            a) while loops to Check if the next line .strip() == ''
            b) if yes, iterate line number,
            c) if no: check if previous line was "blank":
            d) if yes, then add to list of paragraphs a new paragraph,
            e) if no, add line to current paragraph (list[paragraph number])
    
    Update:  ^ This was not the way. Spaghetti code solves all lol
    """
    file = open(fname,encoding='utf8')
    para_list = [[]]
    line_list = []
    p_i = 0
    for line in enumerate(file): #line[0] is the line index, line[1] is the line string
        line_list.append(line[1].rstrip())
        
        if line_list[line[0]] != "":
            if line[0] != 0 and line_list[line[0] - 1] != "":
                para_list[p_i].append(line_list[line[0]])
            elif line[0] != 0 and line_list[line[0] - 1] == "":
                para_list.append(list())
                p_i +=1
                para_list[p_i].append(line_list[line[0]])
            if line[0] == 0:
                para_list[p_i].append(line_list[line[0]])            
    #print(para_list[14]) Testing to make sure .rstrip() works for leading whitespace with my function
    file.close()
    return para_list        

def get_line(fname,parno,lineno):
    para_list = get_paragraph_list(fname)
    return para_list[parno][lineno]
    
def parse_line(line):
    if line.count("/") >= 3:
        temp_split = line.split("/")
        try:
            last_three_integers = (int(temp_split[-3]),int(temp_split[-2]),int(temp_split[-1])) #lots of tuples and lists initialized, messy but works
            remaining_strings = list(temp_split[i] for i in range(0,len(temp_split)-3)) #wanted to messed around with generator objects
            s = ""
            for j in range(len(remaining_strings)):
                if j != len(remaining_strings) - 1:
                    s += remaining_strings[j] + "/"
                else:
                    s+= remaining_strings[j]
            return (last_three_integers[0],last_three_integers[1],last_three_integers[2],s)
        except:
            print("Line Parsing Failure, Most likely error in get_paragraph_list() or get_line() functions if using correct indices. Wow this error message sucks good luck finding the problem")
            return None
    print("Line Parsing Failure, Most likely error in get_paragraph_list() or get_line() functions if using correct indices.  Wow this error message sucks good luck finding the problem")
    return None

def create_program():
    f = open("program.py","w")
    start = check2()
    parsed_line = parse_line(start)
    while(parsed_line[3] != "END"):
        print(parsed_line)
        f.write(parsed_line[3] + "\n")
        parsed_line = parse_line(get_line(str(parsed_line[0]) + '.txt',parsed_line[1]-1,parsed_line[2]-1))
    f.close()




if __name__ == "__main__":
   #test = get_paragraph_list("4.txt") TESTING
   #print(test[41][13])                TESTING
   #print(test[39][1])                 TESTING
   create_program()

