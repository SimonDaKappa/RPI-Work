char = input('Enter frame character ==> ')
print(char)
h = int(input("Height of box ==> "))
print(h)
w = int(input("Width of box ==> "))
print(w)
print("\nBox:")

#I had to do this in paper like 10 times with different scenarios to figure out bruh. Actually have 7 pages of scrap paper bruh sound
str1 = str(w) + "x" + str(h)
s_len = len(str1)
leftoverW = w-2-s_len
leftoverH = h-2-1
left = int(leftoverW/2)
right = leftoverW - left
top = int(leftoverH/2)
bot = leftoverH - top
print(char*w)
middlerow = char + (w-2)*" " + char + "\n"
midmid = char + left*" " + str1 + right*" " + char
print(middlerow*top,end='')
print(midmid)
print(middlerow*bot,end='')
print(char*w)

