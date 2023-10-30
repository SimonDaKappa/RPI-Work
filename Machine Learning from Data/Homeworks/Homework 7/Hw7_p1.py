import numpy as np
import matplotlib.pyplot as plt


def parseToData(path):
  file = open(path, "r")
  data = []
  for line in file:
    line = line.strip()
    line = line.split(" ")
    data.append(parseToDatapoint(line))
  return data

def parseToDatapoint(line):
  value = [float(line[i]) for i in range(1,len(line))]
  label = float(line[0])
  return value, label

def filterData(data, labels):
  filtered = []
  for i in range(len(data)):
    if data[i][1] not in labels:
      continue
    filtered.append(data[i])
  return filtered

def calcIntensity(data):
  intensity = []
  for i in range(len(data)):
    intensity.append(sum(data[i][0])/len(data[i][0]))
  return intensity

def calcSymmetry(data):
  symmetry=[]
  for i in range(len(data)):
    rev = list(reversed(data[i][0]))
    assymetry= 0
    for j in range(len(data[i][0])):
      assymetry += abs(data[i][0][j] - rev[j])
    assymetry /= len(data[i][0])
    symmetry.append(1-assymetry)
  return symmetry
   
def createFromFeatures(feature1, feature2, includeBias = True):
  assert(len(feature1) == len(feature2))
  if includeBias:
    return np.array([[1 , feature1[i], feature2[i]] for i in range(len(feature1))])
  else:
    return np.array([[feature1[i], feature2[i]] for i in range(len(feature1))])

def createData(path, labels, includeBias = True):
  data = parseToData(path)
  data = filterData(data, labels)
  intensity = np.array(calcIntensity(data))
  intensity += abs(np.mean(intensity))
  symmetry = calcSymmetry(data)
  assert(len(intensity) == len(symmetry) == len(data))
  return createFromFeatures(intensity, symmetry, includeBias), np.array([1 if labels[0] == data[i][1] else -1 for i in range(len(data))])

def filterByCondition(w, Z): # Returns indices of X_n that satisfy condition w^T phi(x_n) < 0.015
  #print(str([val[i] for i in range(len(val)) if abs(val[i]) < 0.05]))
  val = np.array([np.dot(w, Z[i]) for i in range(len(Z))])
  return np.array([i for i in range(len(val)) if abs(val[i]) < 0.015])


def plotSeparator(weights, Data, Labels, title, doTransform=False):
  
  # Bias INCLUDED
  class1 = np.array([ Data[i][1:] for i in range(len(Data)) if Labels[i] == 1])
  class1x, class1y = list(zip(*class1))
  class2 = [ Data[i][1:] for i in range(len(Data)) if Labels[i] == -1]
  class2x, class2y = list(zip(*class2))
  Intensity = class1x+class2x
  Symmetry = class1y+class2y
  plt.figure()   
  plt.scatter(class1x, class1y, c="blue", marker = "o")
  plt.scatter(class2x, class2y, c="red", marker = "x")
  
  if doTransform:
    # Basically a homemade desmos for plotting implicit function
    plane = np.array([ [1, np.random.uniform(min(Intensity), max(Intensity)), np.random.uniform(min(Symmetry), max(Symmetry))] for _ in range(250000)])
    transformed = transform3(plane)
    idxs = filterByCondition(weights, transformed)
    plane = np.array([[plane[i][1], plane[i][2]] for i in idxs])
    if len(plane) > 0:
      plt.scatter(plane[:,0], plane[:,1], marker = ".", label = "Separator")
      
  else:
    linspace = np.linspace(min(Intensity),max(Intensity),1000)
    sep = -weights[1]/weights[2] * linspace - weights[0]/weights[2]
    plt.plot(linspace, sep, label = "Separator")
  
  plt.legend()
  plt.title(title + " Separator")
  plt.xlabel("Intensity")
  plt.ylabel("Symmetry")
  plt.xlim(min(Intensity), max(Intensity))
  plt.ylim(min(Symmetry),max(Symmetry))
  plt.savefig(title + " Separator.pdf")

  
def linRegErr(w, X, y):
  sum = 0
  wt = np.transpose(w)
  for i in range(len(X)):  
    sum+= np.power(np.matmul(wt, X[i]) - y[i], 2)
  return sum/len(X)

def logRegErr(w, X, y):
  sum = 0
  wt = np.transpose(w)
  for i in range(len(X)):
    sum+= np.log(1+np.exp(-y[i]*np.matmul(wt, X[i])))
  return sum/len(X)

def pocketAlgorithm(X, y, w, numIterations = 1000):
  for _iter in range(numIterations):
    w_updated = False
    for i in range(len(X)):
      if np.sign(np.matmul(np.transpose(w), X[i])) != y[i]:
        w_temp = w + y[i]*X[i]
        #print(str.format("Updating w, new Ein = {}", calcError(w_temp, X, y)))
        if linRegErr(w_temp, X, y) < linRegErr(w, X, y):
          w = w_temp
          w_updated=True
          break
    if not w_updated:
      break
  return w

def linearRegression(X, y, doPocket = False):
  # returns the separator w = [bias, w1, w2]
  #print(str.format("X: {0}, y: {1}", X.shape, y.shape))
  X_pinv = np.linalg.pinv(X)
  #print(str.format("X_pinv: {}",X_pinv))
  w_lin = np.matmul(X_pinv, y)
  if doPocket:
    w_lin = pocketAlgorithm(X, y, w_lin, len(X))
  return w_lin 
 
def logisticFunc(s):
  return (np.exp(s))/(1+np.exp(s)) 

def logisticGrad(w, X, y, batch_size):
  grad = 0
  # For each data point, calculate the gradient of the logistic function, then sum
  for i in range(batch_size):
    grad+= -y[i]*X[i]/(1+np.exp(y[i]*np.matmul(np.transpose(w), X[i])))
  return grad/len(X)
 
def logisticStochGrad(w, X, y):
  i = np.random.randint(0,len(X))
  return -y[i]*X[i]/(1+np.exp(y[i]*np.matmul(np.transpose(w), X[i])))
 
def logisticRegression(X,y, eta = 0.05,  numIter = 10000, doSGD = True):
  w = np.zeros(X.shape[1])
  batch_size = len(X)
  for t in range(numIter):
    if doSGD:
      v = -logisticStochGrad(w, X, y)
    else:
      v = -logisticGrad(w, X, y, batch_size)
    w+=eta * v
    if np.linalg.norm(v) < 0.001:
      # Converged
      break
  return w

def generalizationBound(err, N, delta):
  return err + np.sqrt(1/(2*N) * np.log(2/delta))

def transform3(X):
  #ret = np.array([[1, X[i][1], X[i][2]**2] for i in range(len(X))])
  # Of form phi(x)^T phi(z) = (1+x^Tz)^2 
  ret = np.array([[1, X[i][1], X[i][2], X[i][1]**2, X[i][1]*X[i][2], X[i][2]**2, X[i][1]**3, X[i][1]**2 * X[i][2], X[i][2]**2 * X[i][1], X[i][2]**3] for i in range(len(X))])
  return ret
 
  
def runAlgorithm(func, errfunc, title, Data, Labels, Data_test, Labels_test, doTransform = False, options = []):
  if doTransform:
    Z = transform3(Data)
    Z_test = transform3(Data_test)
    if len(options) > 0:  
      w = func(Z, Labels, *options)
    else:
      w = func(Z, Labels)
    #print("w = " + str(w))
    ein = errfunc(w, Z, Labels)
    etest = errfunc(w, Z_test, Labels_test)
  else:  
    if len(options) > 0:
      w = func(Data, Labels, *options)
    else:
      w = func(Data, Labels)
    ein = errfunc(w, Data, Labels)
    etest = errfunc(w, Data_test, Labels_test)
  plotSeparator(w, Data, Labels, title, doTransform = doTransform)
  plotSeparator(w, Data_test, Labels_test, title + " test", doTransform = doTransform)
  print(str.format("{}: w = {}", title, w))
  print(str.format("{}: Ein = {}", title, ein))
  print(str.format("{}: E_test = {}", title, etest))
  
  return w, ein, etest


if __name__ == "__main__":
  # 1 = Lin Reg, 2 = Log Reg w/ GD, 3 = Log Reg w/ SGD
  doTransform = True
  path_train, path_test = "zip.train", "zip.test"
  labels = [1,5]
  Data, Labels = createData(path_train, labels, includeBias = True)
  Data_test, Labels_test = createData(path_test, labels, includeBias = True)
  Algorithms = ["Linear Regression", "Linear Regression with Pocket", "Logistic Regression with GD", "Logistic Regression with SGD"]
  AlgorithmFuncs = [linearRegression, linearRegression, logisticRegression, logisticRegression]
  ErrorFuncs = [linRegErr, linRegErr, logRegErr, logRegErr]
  Options = [[False],[True],[0.05, 5000, False],[0.05, 10000, True]]
  W, Ein, Etest = [], [], []
  for i in range(0,len(Algorithms)):
    w, ein, etest = runAlgorithm(AlgorithmFuncs[i], ErrorFuncs[i], Algorithms[i],
      Data, Labels, Data_test, Labels_test, doTransform, Options[i])
    W.append(w)
    Ein.append(ein)
    Etest.append(etest)
  
  Ein_argmin = np.argmin(Ein)
  Etest_argmin = np.argmin(Etest)
  print(str.format("Optimal Ein: {} -> {}, Bound = {}", Algorithms[Ein_argmin], Ein[Ein_argmin], generalizationBound(Ein[Ein_argmin], len(Data), 0.05)))
  print(str.format("Optimal Etest: {} -> {}, Bound = {}", Algorithms[Etest_argmin], Etest[Etest_argmin], generalizationBound(Etest[Etest_argmin], len(Data_test), 0.05)))
    
  