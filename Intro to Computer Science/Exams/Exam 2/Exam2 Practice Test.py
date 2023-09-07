"""
Exam 2 Practice  Test: Learning to use submitty built in code and timer.
Simon Gibson
"""
def distance(tuple1,tuple2):# X-Y Coordinates
    return (((tuple2[1] - tuple1[1])**2 + (tuple2[0]-tuple1[0])**2)**(1/2),tuple1,tuple2)

if __name__ == "__main__":
    L = [(0, 0), (0, 1), (9, 5)]
    distances = []
    for i in range(len(L) - 1):
        distances.append(distance(L[i],L[i+1]))
        
zipped = list(zip(*distances))
min_dist = min(zipped[0])

foo = distances[0].index(min_dist)
print(foo,zipped[1][foo],zipped[2][foo])
