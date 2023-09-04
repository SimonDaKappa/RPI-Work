import matplotlib.pyplot as plt
import numpy as np

def plotfeasible():
  d = np.linspace(-2,8,300)
  x,y = np.meshgrid(d,d)
  plt.imshow((    (4*x-y <= 8) & (2*x+y <= 10) & (5*x-2*y >= -2) & (x >= 0) & (y >= 0)).astype(int), 
             extent=(x.min(),x.max(),y.min(),y.max()),origin="lower", cmap="Greys", alpha = 0.3)
  
  x1 = np.linspace(-2,8,2000)
  yvert = np.linspace(-2,8,2000)
  y1 = 4*x1 - 8
  y2 = 10-2*x1
  y3 = (5*x1+2)/2
  y4 = 0*x1
  
  plt.plot(x1,y1, label = "4x-y <= 8")
  plt.plot(x1,y2, label = "2x+y <= 10")
  plt.plot(x1,y3, label = "5x-2y >= -2")
  plt.plot(x1,y4, label = "x >= 0")
  plt.plot(np.zeros(2000),yvert, label = "y >= 0")
  plt.xlim(-2,8)
  plt.ylim(-2,8)
  plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
  plt.show(block=True)


if __name__ == "__main__":
  plotfeasible()
  # Optimal Point (2,6), Optimal Value 8
  