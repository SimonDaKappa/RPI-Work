import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
  plt.figure()
  data = np.array([[1,0], [-1,0]])
  plt.scatter(data[:,0], data[:,1], c = ['r', 'b'])
  xs = np.linspace(-1,1,100)
  plt.plot([0 for x in xs], xs, label = 'x space plane')
  plt.plot(xs, xs**3, label = 'z space plane')
  plt.legend()
  plt.savefig("test.png")