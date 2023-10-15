import matplotlib.pyplot as plt
from math import sin, cos, radians, pi, sqrt
import numpy as np


def generateDisks(N, sep = 1, rad = 1, thk = .2):
  # Each point on the disk is a (angle, radius) tuple
  # So generate N points on a disk of thickness thk, map top and bottom half
  # to separate rings and shift top left by dst/2 and bottom right by dst/2
  Angles = np.random.uniform(0,2*pi, N)
  Radius = np.random.uniform(rad, rad+thk, N)
  X = Radius * np.cos(Angles)
  Y = Radius * np.sin(Angles)
  TY, TX, BY, BX = list(),list(),list(),list()
  for i in range(N):
    if Y[i] > 0:
      TY.append(Y[i])
      TX.append(X[i])
    else:
      BY.append(Y[i])
      BX.append(X[i])
  TX = np.array(TX)
  TY = np.array(TY)
  BX = np.array(BX)
  BY = np.array(BY)  
    
  TX -= rad/2
  BX += rad/2
  TY += sep/2
  BY -= sep/2

  return TX,TY,BX,BY

def PLA(Data, iters):
  w = np.array([0,0])
  iters = N*10
  converged = False
  count = 0
  for _ in range(iters):
    count+=1
    if converged:
      break
    for i in range(len(Data)):
      sign = np.sign(np.matmul(np.transpose(w), Data[i]))
      
      if sign != np.sign(Data[i][1]):
        # Misclassified
        x = Data[i]
        y = np.sign(Data[i][1])
        #print(str.format("w = {} Miscllassified: ({},{}) sign(w^Tx) == y: {}", w, x[0],x[1], sign == y))
        
        w = w + y*x
        sign = np.sign(np.matmul(np.transpose(w), Data[i]))
        #print(str.format("w = {} Updated: ({},{}) sign(w^Tx) == y: {}", w, x[0], x[1], sign == y))
        break
        
      if i == len(Data)-1:
        converged = True
        break
  return w, count


if __name__ == "__main__":
  N = 2000
  rad = 10
  thk = 5
  doBounds = True
  sep = np.arange(0.2,5.2,0.2)
  convergence_iters = list()
  bounds = list()
  print(sep)
  for s in sep:
    TX, TY, BX, BY = generateDisks(N,s,rad,thk)
    
    Positives = np.array(list(zip(TX,TY)))
    Negatives = np.array(list(zip(BX,BY)))
    Data = np.concatenate((Positives, Negatives))
    #print(Data)
    
    wPLA, ci = PLA(Data, N*10)
    print(str.format("sep = {} | count = {}",s,ci))
    convergence_iters.append(ci)
    if doBounds:
      Y = np.array([Data[i][1] for i in range(len(Data))])
      rho = np.max(Y * np.matmul(Data,wPLA))
      print(rho)
      Xnorms = np.array([np.sqrt(Data[i][0]**2 + Data[i][1]**2) for i in range(len(Data))])
      R = max(Xnorms)
      wNormSquared = wPLA[0]**2+wPLA[1]**2
      bounds.append(rho**2 * wNormSquared / R**2)
    
  plt.plot(sep, convergence_iters, marker = ".", label = "Actual Iteration Count")
  if doBounds:
    plt.plot(sep, bounds, color = "red",label = "Problem 1.3 Bound")
  plt.xlabel("Separation")
  plt.ylabel("PLA Convergence Iterations")
  plt.legend()
  plt.savefig("sepvsiter_bounded.pdf")
  