import numpy as np
import matplotlib.pyplot as plt
from mathHelper import *
from Hw9 import *

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

def calcIntensity(data, normalize = False):
  intensity = []
  for i in range(len(data)):
    intensity.append(sum(data[i][0])/len(data[i][0]))
  if normalize:
    intensity = (intensity-np.mean(intensity))
  return intensity

def calcSymmetry(data, normalize = True):
  symmetry=[]
  for i in range(len(data)):
    rev = list(reversed(data[i][0]))
    assymetry= 0
    for j in range(len(data[i][0])):
      assymetry += abs(data[i][0][j] - rev[j])
    assymetry /= len(data[i][0])
    symmetry.append(1-assymetry)
    
  if normalize:
    symmetry = (symmetry-np.mean(symmetry))
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

def plotSeparator(weights, Data, Labels, title, doTransform=False, transformFunc = None):
  
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
  
  if doTransform and transformFunc is not None:
    x, y = np.meshgrid(np.linspace(min(Intensity), max(Intensity), 100), np.linspace(min(Symmetry), max(Symmetry), 100))
    eq = transformFunc(list(zip(x.flat, y.flat)))
    eq = np.array([np.dot(eq[i],weights) for i in range(len(eq))]).reshape(len(x),len(y))
    plt.contour(x, y, eq, [0], colors = "black")
  else:
    linspace = np.linspace(min(Intensity),max(Intensity),1000)
    sep = -weights[1]/weights[2] * linspace - weights[0]/weights[2]
    plt.plot(linspace, sep, label = "Separator")
  if not doTransform:
    plt.legend()
  plt.title(title + " Separator")
  plt.xlabel("Intensity")
  plt.ylabel("Symmetry")
  plt.xlim(min(Intensity), max(Intensity))
  plt.ylim(min(Symmetry),max(Symmetry))
  plt.savefig(title + " Separator.pdf")
  
def runAlgorithm(func, errfunc, title, Data, Labels, doCV = False, errfunc_cv = None, CV_options = [], doTransform = False, transformFunc = None, options = []):
  idx = np.array([i for i in range(len(Data))])
  chosen_idxs = np.random.choice(idx, size = len(Data) - int(2*len(Data)/5), replace = False)
  #chosen_idxs = np.random.choice(idx, size = 300, replace = False)
  D_train = Data[chosen_idxs]
  L_train = Labels[chosen_idxs]
  Data_test = np.delete(Data, chosen_idxs, axis = 0)
  Labels_test = np.delete(Labels, chosen_idxs, axis = 0)
  Data, Labels = D_train, L_train
  
  if doCV and len(CV_options) > 0:
    Ein = []
    Etest = []
    weights = []
    for reg_param in CV_options:
      print(str.format("CV: reg_param = {}", reg_param))
      if doTransform and transformFunc is not None:
        Z = transformFunc(Data)
        Z_test = transformFunc(Data_test)
        if len(options) > 0:  
          w = func(Z, Labels, *options)
        else:
          w = func(Z, Labels)
        #print("w = " + str(w))
        Ein.append(errfunc_cv(Z, Labels, reg_param))
      else:
        if len(options) > 0:
          w = func(Data, Labels, reg_param, *options)
        else:
          w = func(Data, Labels, reg_param)
        Ein.append(errfunc_cv(Data, Labels, reg_param))
      weights.append(w)
      Etest.append(errfunc(w, Z_test, Labels_test) if doTransform else errfunc(w, Data_test, Labels_test))
    w = weights[np.argmin(Ein)]
    best_option = CV_options[np.argmin(Ein)]
    etest = errfunc(w, Z_test, Labels_test) if doTransform else errfunc(w, Data_test, Labels_test)
    ein = min(Ein)
    
    with open(title + " CV.txt", "w") as file:
      file.write(str(CV_options) + "\n" + str(Ein) + "\n" + str(Etest))
      file.close()
    plt.figure()
    plt.plot(CV_options, Ein, label = "Ein")
    plt.plot(CV_options, Etest, label = "Etest")
    plt.xlabel("Regularization Parameter")
    plt.ylabel("CV Error")
    plt.legend()
    plt.title(title + " CV Error")
    plt.savefig(title + " CV Error.pdf")
    print(str.format("{} Regularized: Best option = {}, Ecv* = {}", title, best_option, min(Ein)))
    title += str.format(" lambda = {}", best_option)
  else:
    if doTransform and transformFunc is not None:
      Z = transformFunc(Data)
      Z_test = transformFunc(Data_test)
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
   
  #print(str.format("Pre plotSeperator: w = {}", w))
  plotSeparator(w, Data, Labels, title, doTransform = doTransform, transformFunc = transformFunc)
  plotSeparator(w, Data_test, Labels_test, title + " test", doTransform = doTransform, transformFunc = transformFunc)
  print(str.format("{}: Ein = {}", title, ein))
  print(str.format("{}: E_test = {}", title, etest))
  #print(str.format("{}: w = {}", title, w))
  
  return w, ein, etest


if __name__ == "__main__":
  # 1 = Lin Reg, 2 = Log Reg w/ GD, 3 = Log Reg w/ SGD
  doTransform = True
  doCV = True
  #CV_options = [2]
  CV_options = np.arange(0, 2, .01)
  transformFunc = polyTransform
  path_train, path_test = "zip.train", "zip.test"
  labels = [1,2,3,4,5,6,7,8,9]
  Data, Labels = createData(path_train, labels, includeBias = True)
  Data_test, Labels_test = createData(path_test, labels, includeBias = True)
  Data, Labels = np.concatenate((Data, Data_test)), np.concatenate((Labels, Labels_test))
  print(len(Data))
  Algorithms = ["Linear Regression", "Linear Regression with Pocket", "Logistic Regression with GD", "Logistic Regression with SGD"]
  AlgorithmFuncs = [linearRegression, linearRegression, logisticRegression, logisticRegression]
  ErrorFuncs = [linRegErr, linRegErr, logRegErr, logRegErr]
  Options = [[False],[True],[0.05, 5000, False],[0.05, 10000, True]]
  W, Ein, Etest = [], [], []
  
  
  
  # Run the algorithms 
  for i in range(0,1):
    w, ein, etest = runAlgorithm(AlgorithmFuncs[i], ErrorFuncs[i], Algorithms[i], Data, Labels, doCV, 
                                 linRegCVErr, CV_options, doTransform, transformFunc, Options[i])
    W.append(w)
    Ein.append(ein)
    Etest.append(etest)
  
  Ein_argmin = np.argmin(Ein)
  Etest_argmin = np.argmin(Etest)
  print(str.format("Optimal Ein: {} -> {}, Eout Bound = {}",
                   Algorithms[Ein_argmin], Ein[Ein_argmin], 
                   generalizationBound(Ein[Ein_argmin], len(Data), 0.03)))
  print(str.format("Optimal Etest: {} -> {}, Eout Bound = {}", 
                   Algorithms[Etest_argmin], Etest[Etest_argmin], 
                   generalizationBound(Etest[Etest_argmin], len(Data_test), 0.03)))
    
  