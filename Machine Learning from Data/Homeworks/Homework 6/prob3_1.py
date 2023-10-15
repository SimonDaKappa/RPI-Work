import matplotlib.pyplot as plt
from math import sin, cos, radians, pi, sqrt
import numpy as np
import time

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
  for _ in range(iters):
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
  return w

def LR(Data):
  Y = [np.sign(Data[i][1]) for i in range(len(Data))]
  print(Data.shape)
  XTX = np.matmul(np.transpose(Data),Data)
  try:
    XTXinv = np.linalg.inv(XTX)
    print(str.format("{}, {}",XTX.shape, XTXinv.shape))
    pseudoInverse = np.matmul(XTXinv, np.transpose(Data))
    return np.matmul(pseudoInverse, Y)
  except TypeError as err:
    print(err)
    return [0,0]
    
  


if __name__ == "__main__":
  N = 2000
  rad = 10
  thk = 5
  sep = 5
  TX, TY, BX, BY = generateDisks(N,sep,rad,thk)
  
  Positives = np.array(list(zip(TX,TY)))
  Negatives = np.array(list(zip(BX,BY)))
  Data = np.concatenate((Positives, Negatives))
  #print(Data)
  
  t0 = time.time()
  wPLA = PLA(Data, N*10)
  t1 = time.time() - t0   
  wLR = LR(Data)
  t2 = time.time() - t1 - t0
  print(str.format("Performance: PLA {} | LR {}", t1, t2))
  print(str.format("PLA separator y = {}x", -wPLA[0]/wPLA[1]))
  print(str.format("LR separator y = {}x", -wLR[0]/wLR[1]))
  linex = np.linspace(-20,20, 100)
  lineyPLA = -wPLA[0]/wPLA[1] * linex 
  lineyLR = -wLR[0]/wLR[1] * linex
  plt.plot(linex,lineyPLA, label = "PLA")
  plt.plot(linex,lineyLR, label = "LR")
  plt.scatter(TX,TY, marker = "+", color = "blue")
  plt.scatter(BX,BY, marker = "_", color = "red")
  plt.legend()
  plt.savefig("Scatter.pdf")      
  