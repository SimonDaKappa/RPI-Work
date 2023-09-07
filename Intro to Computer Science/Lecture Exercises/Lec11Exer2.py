""" FUNCTIONS AREA: Scuffed sort algorithm, probably easiest just to do iterated sort bc thats all i remember how to do"""

def sort_height(height1,heigh2,height3):
    heights = [height1,heigh2,height3]
    names = ["Dale","Erin","Sam"] 
    for i in range(len(heights)):
        max_i = i
        for j in range(i + 1, len(heights)):
            if heights[max_i] < heights[j]:
                max_i = j
        heights[i], heights[max_i] = heights[max_i], heights[i] 
        names[i], names[max_i] = names[max_i], names[i]
        
    for x in names:
        print(x)
        124


"""MAIN BODY:"""

h1 = input("Enter Dale's height: ")
print(h1)
h2 = input("Enter Erin's height: ")
print(h2)
h3 = input("Enter Sam's height: ")
print(h3)
sort_height(h1,h2,h3)

