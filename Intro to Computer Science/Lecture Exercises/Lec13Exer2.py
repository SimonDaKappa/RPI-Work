inp = input("Enter the scores file: ")
print(inp)
out = input("Enter the output file: ")
print(out)


i = open(inp,"r")
o = open(out,"w")

scorelist = i.read().split("\n")
scorelist = sorted(scorelist, key=int)
c = 0
for x in scorelist:
    x = int(x)
    writestring = "{:2d}: ".format(c) + "{:3d}".format(x)+ "\n"
    o.write(writestring)
    print(writestring,end='')
    c+=1
o.close()
    
    



