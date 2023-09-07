"""
Simon Gibson - Exam 2 Question 2
"""

def generate_pascal_triangle(size):
    tri = [[1] for x in range(size)] #Could do this but the math would be tricky maybe? Ill try and see where it goes. 
    for i in range(len(tri)): #loops over each row 
        for j in range(1,i + 1): #loops over each value in the row thats not the 0th
            try:
                tri[i].append(tri[i-1][j] + tri[i-1][j - 1])
            except:
                tri[i].append(1) #this should work on its own, the only time the try case should be false is the 2nd step of the triangle where you generate "1 1", i hope.
    print_pascal(tri)
    
def print_pascal(tri):
    print(tri)
    for i in range(len(tri)):
        for j in range(len(tri[i])):
            print(tri[i][j],end = ' ')
        print()
    
    

if __name__ == "__main__":
    size = int(input("Please enter the number of sublists: "))
    generate_pascal_triangle(size)