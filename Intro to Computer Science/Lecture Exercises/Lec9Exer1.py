def multiples(i): #prints multiples of 3 that are less than i
    if i < 3:
        print("0")
    else:
        c = 0
        while(c * 3 < i):
            print(c*3)
            c+= 1

i = int(input("Enter a positive integer: "))
print(i)
multiples(i)