import numpy as np
import matplotlib.pyplot as plt

def condition(x):
  #print(x.shape)
  return abs(-x[0]**2 + x[1]) < 0.004

data = np.array([[np.random.uniform(-1,1), np.random.uniform(-1,1)] for i in range(500000)])
print(data.shape)
filtered = np.array([x for x in data if condition(x)])
print(filtered.shape)


plt.figure()
plt.plot(filtered[:,0], filtered[:,1], ',')
plt.savefig("Test2.pdf")


plane = np.array([ [1, np.random.uniform(min(Intensity), max(Intensity)), np.random.uniform(min(Symmetry), max(Symmetry))] for _ in range(500000)])
    transformed = transform3(plane)
    print(str.format("transformed: {}", transformed.shape))
    idxs = filterByCondition(weights, transformed)
    print(str.format("idxs: {}", idxs.shape))
    plane = np.array([[plane[i][1], plane[i][2]] for i in idxs])
    print(str.format("plane: {}", plane.shape))
    if len(plane) > 0:
      plt.plot(plane[:,0], plane[:,1], marker = ".", label = "Separator")