import numpy as np
from statistics import mode

class kNN:
  def __init__(self, k):
    self.k = k
    self.X = np.array([])
    self.Y = np.array([])
    
  def fit(self, X, Y):
    if X.shape[0] != Y.shape[0]:
      raise ValueError("X and Y must have the same number of rows")
    if self.X.shape[0] == 0 and self.Y.shape[0] == 0:
      self.X = X
      self.Y = Y
    else:
      self.X = np.concatenate((self.X, X))
      self.Y = np.concatenate((self.Y, Y))
    
  def predict(self, X):
    pred = []
    for i in range(len(X)):
      pred.append(self._predict(X[i]))
    return np.array(pred)
  
  def _predict(self, x):
    # Sort Y by norms of x to all points in X
    norms = np.array([np.linalg.norm(x-self.X[i])
                     for i in range(self.X.shape[0])])
    classes_sorted = self.Y[np.argsort(norms)]
    # Get the k nearest neighbors
    k_nearest = classes_sorted[:self.k]
    
    # Get the most frequent class
    return mode(k_nearest)