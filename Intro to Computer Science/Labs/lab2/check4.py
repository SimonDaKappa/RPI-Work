first = input("Please enter you first name: ")
print(first)
last = input("Please enter youlast name: ")
print(last)
firstl = len(first)
lastl = len(last)

if firstl < 6 and lastl < 6:
    big = 6
elif firstl > lastl:
    big = firstl
else:
        big = lastl
print(big)
linelength = big+6

print("*"*linelength)
print("** ","Hello,",' ' * (linelength - 11),"**",sep='')
print("** ",first,' '*(linelength-(firstl+5)),"**" ,sep='')
print("** ",last,' ' * (linelength -(lastl+5)),"**",sep='')
print("*"*linelength)