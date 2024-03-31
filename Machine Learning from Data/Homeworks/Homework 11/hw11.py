import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np
from Hw9 import *
from kNN import *
from RBFNetwork import *
import time

def plotDecisionBoundary(X, Y, k, classifier):
  xmin, xmax = np.min(X[:,0]), np.max(X[:,0])
  ymin, ymax = np.min(X[:,1]), np.max(X[:,1])
  print(xmin, xmax, ymin, ymax)
  xx, yy = np.meshgrid(np.linspace(xmin, xmax, 100), np.linspace(ymin, ymax, 100))
  clf = classifier(k)
  clf.fit(X, Y)
  pred = clf.predict(np.c_[xx.ravel(), yy.ravel()])

  cmap_light = ListedColormap(['#FFAAAA', '#AAFFAA'])
  cmap_bold = ListedColormap(['#FF0000', '#00FF00']) 
  # Put the result into a color plot
  pred = pred.reshape(xx.shape)
  plt.figure() 
  print(xx.shape, yy.shape, pred.shape)
  plt.pcolormesh(xx, yy, pred, cmap=cmap_light)
  # Plot also the training points
  plt.scatter(X[:, 0], X[:, 1], c = Y, cmap=cmap_bold)
  plt.xlim(xx.min(), xx.max())
  plt.ylim(yy.min(), yy.max())
  plt.title(str.format("{} Decision Boundary for Optimal k = {}",classifier.__name__, k))
  plt.savefig(str.format("{} Decision Boundary for Optimal k.pdf",classifier.__name__, k))
  
def runClassifier(X, Y, classifier, k):
  
  print("Running " + classifier.__name__ + " with k = " + str(k))
  start_t = time.time()
  clf = classifier(k)
  clf.fit(X, Y)
  fit_t = time.time()
  pred = clf.predict(X)
  pred_t = time.time()
  Ein = np.sum(pred != Y)/len(Y)
  Ecv = kFoldCV(classifier, k, X, Y, 5)
  
  
  print("Ein = " + str(Ein))
  print("Ecv = " + str(Ecv))
  return clf, Ein, Ecv, [fit_t-start_t, pred_t-fit_t]
 
def kFoldCV(classifier, arg, X, Y, k):
  Ecv = 0
  step = len(X)//k
  for i in range(k):
    X_train = np.concatenate((X[:i*step], X[(i+1)*step:]))
    Y_train = np.concatenate((Y[:i*step], Y[(i+1)*step:]))
    X_test = X[i*step:(i+1)*step]
    Y_test = Y[i*step:(i+1)*step]
    clf = classifier(arg)
    clf.fit(X_train, Y_train)
    pred = clf.predict(X_test)
    Ecv += np.sum(pred != Y_test)/len(Y_test)
  return Ecv/k
   
 
    
if __name__ == "__main__":
  labels = [1,2,3,4,5,6,7,8,9]
  path_train, path_test = "zip.train", "zip.test"
  Data, Labels = createData(path_train, labels, includeBias = False)
  Data_test, Labels_test = createData(path_test, labels, includeBias = False)
  Data, Labels = np.concatenate((Data, Data_test)), np.concatenate((Labels, Labels_test))
  
  # Separate 300 random points from into train set
  train_idxs = np.random.choice(len(Data), 300, replace = False)
  Data_train, Labels_train = Data[train_idxs], Labels[train_idxs]
  test_idxs = np.delete(np.array([i for i in range(len(Data))]), train_idxs)
  Data_test, Labels_test = Data[test_idxs], Labels[test_idxs]
  
  
  # kNN
  K = range(1,len(Data_train)//4)
  #K = range(1,10)
  Ein_kNN = []
  Ecv_kNN = []
  times_kNN = []
  classifiers_kNN = []
  for k in K:
    clf, Ein, Ecv, times = runClassifier(Data_train, Labels_train, kNN, k)
    classifiers_kNN.append(clf)
    Ein_kNN.append(Ein)
    Ecv_kNN.append(Ecv)
    times_kNN.append(times)
    
  # Choose best k
  best_k_knn = K[np.argmin(Ein_kNN)]
  best_k_knn_cv = K[np.argmin(Ecv_kNN)]
  print("Best In Sample KNN k: ", best_k_knn)
  print("Best CV KNN k: ", best_k_knn_cv)

  # RBFNetwork
  Ein_RBF = []
  Ecv_RBF = []
  times_RBF = []
  classifiers_RBF = []
  for k in K:
    clf, Ein, Ecv, times = runClassifier(Data_train, Labels_train, RBFNetwork, k)
    classifiers_RBF.append(clf)
    Ein_RBF.append(Ein)
    Ecv_RBF.append(Ecv)
    times_RBF.append(times)
  
  # Choose best k
  best_k_rbf = K[np.argmin(Ein_RBF)]
  best_k_rbf_cv = K[np.argmin(Ecv_RBF)]
  print("Best In Sample k RBF: ", best_k_rbf)
  print("Best CV k RBF: ", best_k_rbf_cv)
  
  # Plot decision boundaries
  plotDecisionBoundary(Data_train, Labels_train, best_k_knn_cv, kNN)
  plotDecisionBoundary(Data_train, Labels_train, best_k_rbf_cv, RBFNetwork)
  
  # Plot E_in vs k
  plt.figure()
  plt.plot(K, Ein_kNN, label = "kNN In-Sample Error")
  plt.plot(K, Ecv_kNN, label = "kNN CV Error")
  plt.scatter([best_k_knn, best_k_rbf], [np.min(Ein_kNN), np.min(Ein_RBF)], marker = "o", color = "red", label = "Minimum In-Sample Errors")
  plt.scatter([best_k_knn_cv, best_k_rbf_cv], [np.min(Ecv_kNN), np.min(Ecv_RBF)], marker = "o", color = "green", label = "Minimum CV Errors")
  plt.plot(K, Ein_RBF, label = "RBFNetwork In-Sample Error")
  plt.plot(K, Ecv_RBF, label = "RBFNetwork CV Error")
  plt.title("Training & Cross Val Errors vs k")
  plt.xlabel("K (NN or Center Count)")
  plt.ylabel("Error")
  plt.legend()
  plt.savefig("Errors vs k.pdf")
  
  # Calculate E_test
  E_test_knn = np.sum(classifiers_kNN[np.argmin(Ecv_kNN)]
                      .predict(Data_test) != Labels_test)/len(Data_test)
  print(str.format("kNN Error for CV optimal k = {}, E_test = {}, E_cv = {}, E_in = {}",best_k_knn_cv, E_test_knn, Ecv_kNN[np.argmin(Ecv_kNN)], Ein_kNN[np.argmin(Ecv_kNN)]))
  E_test_rbf = np.sum(classifiers_RBF[np.argmin(Ecv_RBF)]
                      .predict(Data_test) != Labels_test)/len(Data_test)
  print(str.format("RBF Error for CV optimal k = {}, E_test = {}, E_cv = {}, E_in = {}", best_k_rbf_cv, E_test_rbf, Ecv_RBF[np.argmin(Ecv_RBF)], Ein_RBF[np.argmin(Ecv_RBF)]))
  
  
  
  
  