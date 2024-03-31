import numpy as np
import matplotlib.pyplot as plt

class RBFNetwork:
  def __init__(self, k, r = 0, lambda_ = 0.02):
    self.r = r if r != 0 else 2/np.sqrt(k)
    self.k = k
    self.lambda_ = lambda_
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
    # Generate the means and clusters using lloyds algorithm
    self._lloyds()
    
    # Compute feature matrix and insert bias
    Z = [[self._kernel(x, mu) for mu in self.means] for x in self.X]
    for i in range(len(Z)):
      Z[i].insert(0, 1)
    Z = np.array(Z)
      
    # Compute weights via linear regularized regression
    Z_reg_pinv = np.linalg.inv(np.matmul(Z.T,Z) + self.lambda_*np.identity(Z.shape[1])) 
    self._H = np.matmul(np.matmul(Z, Z_reg_pinv), Z.T)
    self.w = np.matmul(Z_reg_pinv, Z.T.dot(self.Y))
    
  def predict(self, X):
    pred = []
    for i in range(len(X)):
      pred.append(self._predict(X[i]))
    return np.array(pred)
      
  def _predict(self, x):
    # Compute feature vector phi
    phi = np.array([self._kernel(x, mu) for mu in self.means])
    phi = np.insert(phi, 0, 1)
    return np.sign(np.dot(self.w, phi))
    
  def _kernel(self, x, mu):
    return np.exp(-np.linalg.norm(x - mu)/self.r)
    
  def _lloyds(self, num_iters = 10):
    # Generate k partitions greedily
    means = list()
    while len(means) < self.k:
      # Add the point mutually farthest from current means
      means.append(self._mutually_furthest(means)) 
      
    # Initialize clusters
    clusters = [[] for i in range(self.k)]
    for i in range(num_iters):
      # Assign each point to its closest mean
      clusters = [[] for j in range(self.k)] # Reinit each cluster
      for x in self.X:
        clusters[np.argmin([np.linalg.norm(x - mean) for mean in means])].append(x)
      # Update means
      means = [np.mean(cluster, axis = 0) for cluster in clusters]
      
    
    self.means = np.array(means)
    self.clusters = clusters
    
  def _mutually_furthest(self, means):
    if len(means) == 0:
      return self.X[np.random.choice(range(self.X.shape[0]), 1)][0]
    return self.X[np.argmax(np.min([np.linalg.norm(means[i] - self.X, axis = 1) for i in range(len(means))], axis = 0))]
  