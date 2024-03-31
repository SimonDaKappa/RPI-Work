import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np
from sklearn import neighbors
from Hw9 import *
import time

def transform_p61b(X):
  return np.array([np.sqrt(X[:,0]**2 + X[:,1]**2), np.arctan(X[:,1]/X[:,0])]).T

def plotDecisionBoundary(X, Y, k, transformFunc = None):
  xmin, xmax = np.min(X[:,0])-2, np.max(X[:,0])+2
  ymin, ymax = np.min(X[:,1])-2, np.max(X[:,1])+2
  print(xmin, xmax, ymin, ymax)
  xx, yy = np.meshgrid(np.linspace(xmin, xmax, 250), np.linspace(ymin, ymax, 250))
  clf = neighbors.KNeighborsClassifier(k, weights='uniform')
  if transformFunc is not None:
    clf.fit(transformFunc(X), Y)
    print("transformed!")
  else:
    clf.fit(X, Y)
  pred = clf.predict(np.c_[xx.ravel(), yy.ravel()])

  cmap_light = ListedColormap(['#FFAAAA', '#AAFFAA'])
  cmap_bold = ListedColormap(['#FF0000', '#00FF00']) 
  # Put the result into a color plot
  pred = pred.reshape(xx.shape)
  plt.figure()
  if transformFunc is not None:
    xgrid = np.array([xx.ravel(), yy.ravel()]).T
    pred = clf.predict(transformFunc(xgrid)).reshape(xx.shape)
    plt.contourf(xx, yy, pred, cmap=cmap_light)   
  else:
    print(xx.shape, yy.shape, pred.shape)
    plt.pcolormesh(xx, yy, pred, cmap=cmap_light)
# Plot also the training points
  plt.scatter(X[:, 0], X[:, 1], c = Y, cmap=cmap_bold)
  plt.xlim(xx.min(), xx.max())
  plt.ylim(yy.min(), yy.max())
  transform_name = "" if transformFunc is None else transformFunc.__name__
  plt.title(str.format("{} Decision Boundary for k = {}",transform_name, k))
  plt.savefig(str.format("{} Decision Boundary for k = {}.pdf",transform_name, k))
  
def generateDisks(N, sep = 1, rad = 1, thk = .2):
  # Each point on the disk is a (angle, radius) tuple
  # So generate N points on a disk of thickness thk, map top and bottom half
  # to separate rings and shift top left by dst/2 and bottom right by dst/2
  Angles = np.random.uniform(0,2*np.pi, N)
  Radius = np.random.uniform(rad, rad+thk, N)
  X = Radius * np.cos(Angles)
  Y = Radius * np.sin(Angles)
  Data, Labels = list(), list()
  for i in range(N):
    if Y[i] > 0:
      Y[i] += sep/2
      X[i] += rad/2
      Labels.append(1)
    else:
      Y[i] -= sep/2
      Y[i] -= rad/2
      Labels.append(-1)
    Data.append([X[i], Y[i]])
  
  return np.array(Data), np.array(Labels)

def randomSplit(X, Y):
  idx = np.array([i for i in range(len(X))])
  chosen_idxs = np.random.choice(idx, size = 500, replace = False)
  D_train = X[chosen_idxs]
  L_train = Y[chosen_idxs]
  Data_test = np.delete(X, chosen_idxs, axis = 0)
  Labels_test = np.delete(Y, chosen_idxs, axis = 0)
  return D_train, L_train, Data_test, Labels_test

def runCNN(X, Y):
  X_train, Y_train, X_test, Y_test = randomSplit(X, Y)
  clf = neighbors.KNeighborsClassifier(3, weights='uniform')
  # Run on full dataset
  clf.fit(X_train, Y_train)
  Y_trainpred = clf.predict(X_train)
  Y_testpred = clf.predict(X_test) 
  
  Ein = np.sum(Y_trainpred != Y_train)/len(Y_train)
  Etest = np.sum(Y_testpred != Y_test)/len(Y_test)
  
  # Condense dataset
  X_S, idxs_S = condenseData(X_train, Y_train)
  clf.fit(X_S, Y_train[idxs_S])
  Ein_cond = np.sum(clf.predict(X_train) != Y_train)/len(Y_train)
  Etest_cond = np.sum(clf.predict(X_test) != Y_test)/len(Y_test)
  
  return Ein, Etest, Ein_cond, Etest_cond
  
def condenseData(X, Y, s_init_size = 5):  
  clf_S = neighbors.KNeighborsClassifier(3, weights='uniform')
  S = X[0:s_init_size]
  clf_S.fit(S, Y[0:s_init_size])
  idxs = [i for i in range(s_init_size)]
  
  for i in range(len(X)):
    if X[i] not in S and clf_S.predict(X[i].reshape(1,-1)) != Y[i]:
      S = np.append(S, X[i].reshape(1,-1), axis = 0)
      idxs.append(i)
      clf_S.fit(S, Y[idxs])
  #print(len(S))
  return S, idxs
  
def p614():
  labels = [1,2,3,4,5,6,7,8,9]
  path_train, path_test = "zip.train", "zip.test"
  Data, Labels = createData(path_train, labels, includeBias = False)
  Data_test, Labels_test = createData(path_test, labels, includeBias = False)
  Data, Labels = np.concatenate((Data, Data_test)), np.concatenate((Labels, Labels_test))
  
  Ein, Etest, Ein_cond, Etest_cond = [], [], [], []
  for i in range(100):
    print(i)
    ein, etest, ein_cond, etest_cond = runCNN(Data, Labels)
    Ein.append(ein)
    Etest.append(etest)
    Ein_cond.append(ein_cond)
    Etest_cond.append(etest_cond)
  
  print("Ein: ", np.mean(Ein))
  print("Etest: ", np.mean(Etest))
  print("Ein_cond: ", np.mean(Ein_cond))
  print("Etest_cond: ", np.mean(Etest_cond))

def p616(doA = True):
  # Generate  uniform (0,1)^2 square
  
  
  if doA:
    X = np.random.uniform(0,1, size = (10000,2))
  if not doA:
    means = np.random.uniform(0,1, size = (10,2))
    var = 0.1**2
    cov1 = np.array([[var,0], [0, var]])
    gaussian_selection = np.random.uniform(0,1, size = 10000)
    tmp = []
    for i in range(10000):
      tmp.append(np.random.multivariate_normal(means[i%10], cov1))
    X = np.array(tmp)
    print(X.shape)
    
  # Generate 10 partitions greedily 
  p_centers = list()
  p_centers.append(X[np.random.choice([i for i in range(10000)], 1)][0])
  while len(p_centers) < 10:
    p_centers.append(X[np.argmax(np.min([np.linalg.norm(p_centers[i] - X, axis = 1) for i in range(len(p_centers))], axis = 0))])
  # Generate clusters from partitions
  if not doA:
    p_centers = means
  clusters = np.zeros((10,0)).tolist()
  for i in range(10000):
    clusters[np.argmin(np.linalg.norm(p_centers - X[i], axis = 1))].append(X[i])
  # Find mean of each cluster
  c_means = np.zeros((10,0)).tolist()
  for i in range(len(clusters)):
    c_means[i] = np.mean(np.array(clusters[i]), axis = 0)
  # Find cluster radius
  c_radii = np.zeros((10,0)).tolist()
  for i in range(len(clusters)):
    c_radii[i] = np.max(np.linalg.norm(np.array(clusters[i]) - c_means[i], axis = 1))
  
  X_test = np.random.uniform(0,1, size = (1000,2))
  
  # Find nearest neighbor to each point
  t1 = time.time()
  for i in range(len(X_test)):
    nn = np.argmin(np.linalg.norm(X_test[i] - X, axis = 1))
  t2 = time.time()
  
  # Find nearest neighbor using branch and bound
  t3 = time.time()
  for i in range(len(X_test)):
    closest_cluster = np.argmin(np.linalg.norm(X_test[i] - np.array(c_means), axis = 1))
    nn_cc = np.argmin(np.linalg.norm(X_test[i] - np.array(clusters[closest_cluster]), axis = 1))  
    if np.linalg.norm(X_test[i] - X[nn_cc]) <= np.linalg.norm(X_test[i] - c_means[closest_cluster]) - c_radii[closest_cluster]:
      continue
    else:
      for j in range(len(clusters)):
        if j != closest_cluster:
          nn_cc = np.argmin(np.linalg.norm(X_test[i] - np.array(clusters[j]), axis = 1))
          if np.linalg.norm(X_test[i] - X[nn_cc]) <= np.linalg.norm(X_test[i] - c_means[j]) - c_radii[j]:
            break
  t4 = time.time() 
  
  print("Time for NN: ", t2-t1)
  print("Time for NN with B&B: ", t4-t3)
  
  tab10 = plt.get_cmap("tab10")
  p_centers = np.array(p_centers).T
  print(p_centers.shape)
  plt.figure()
  plt.scatter(p_centers[0], p_centers[1], marker = "x", color = "red")
  for i in range(len(clusters)):
    plt.scatter(np.array(clusters[i])[:,0], np.array(clusters[i])[:,1], color = tab10(i), alpha = .1, marker = ".")
  plt.savefig("test.pdf")
  
  
if __name__ == "__main__":
  #X = np.array([[1,0],[0,1],[0,-1],[-1,0],[0,2],[0,-2],[-2,0]])
  #Y = np.array([-1,-1,-1,-1,1,1,1])
  #assert(X.shape[0] == Y.shape[0])
  #plotDecisionBoundary(X, Y, 1)
  #plotDecisionBoundary(X, Y, 3)
  #plotDecisionBoundary(X, Y, 1, transform_p61b)
  #plotDecisionBoundary(X, Y, 3, transform_p61b)
  
  #N, rad, thk, sep = 2000, 10, 5, 5
  #X, Y = generateDisks(N, sep, rad, thk)
  #print(X.shape, Y.shape)
  #plotDecisionBoundary(X, Y, 3)
  p616()
  
  
  