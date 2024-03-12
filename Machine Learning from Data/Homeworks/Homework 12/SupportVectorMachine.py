from cvxopt import matrix, solvers
from cvxopt.solvers import qp
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

class SupportVectorMachine:
  def __init__(self, kernel, C):
    solvers.options['show_progress'] = False
    self.kernel = kernel
    self.C = C
  
  def set_kernel(self, kernel):
    self.kernel = kernel
  
  def set_C(self, C):
    self.C = C
  
  def print_kernel(self, x1, x2):
    print(self.kernel(x1, x2))
    
  def fit(self, X, y):
    m = len(X)
    # Compute Gram matrix
    Gram = np.zeros((m, m))
    for i in range(m):
      for j in range(m):
        Gram[i][j] = y[i]*y[j]*self.kernel(X[i], X[j])
    Gram = matrix(Gram) 
    # Solve Dual QP problem for alphas
    # G matrix is N x 2N matrix where every 2 elements
    # are pairwise zero_constraint, C_constraint
    G = []
    for i in range(m):
      zero_constraint = [0 for j in range(m)]
      zero_constraint[i] = -1
      c_constraint = [0 for j in range(m)]
      c_constraint[i] = 1
      G.extend([zero_constraint, c_constraint])
    # h matrix is 2N x 1 matrix where every 2 elements
    # are 0 and C
    h = []
    for i in range(m):
      h.extend([0, self.C])
    ones = [1 for i in range(m)]
    A = np.array([[y[i]] for i in range(m)]).T
    G = matrix(np.array(G).astype(np.double)) 
    h = matrix(np.array(h).astype(np.double))
    A = matrix(A.astype(np.double))
    b = matrix(np.array([0]).astype(np.double))
    ones = matrix(-1*np.array(ones).astype(np.double))

    # minimize 1/2 alpha.T @ Gram @ alpha + ones.T @ alpha
    #  alpha
    # subject to 0 <= alpha_i <= C, y.T @ alpha = 0
    #
    alpha = qp(P = Gram, q = ones, G = G, h = h, A = A, b = b)
    # Choose index s st 0 < alpha_s < C
    s_idx = -1
    for i in range(len(alpha['x'])):
      if alpha['x'][i] > 0 and alpha['x'][i] < self.C:
        s_idx = i
        break
      
    # recover primal b_star = y[s] - sum_{alpha_i > 0}^N alpha_i y_i K(x_i, x_s)
    self.b_star = y[s_idx] - sum([alpha['x'][i]*y[i]*self.kernel(X[i], X[s_idx]) for i in range(len(alpha['x']))])
    # recover primal hypothesis(x_input) = sign(sum_{alpha_i > 0}^N alpha_i y_i K(x_i, x_input) + b_star) 
    self.hypothesis = lambda x: np.sign(sum([alpha['x'][i]*y[i]*self.kernel(X[i], x) for i in range(len(alpha['x']))]) + self.b_star)
  
  def plotDecisionBoundary(self, X, y):
    xmin, xmax = np.min(X[:,0])-.1, np.max(X[:,0])+.1
    ymin, ymax = np.min(X[:,1])-.1, np.max(X[:,1])+.1
    print(xmin, xmax, ymin, ymax)
    xx, yy = np.meshgrid(np.linspace(xmin, xmax, 100), np.linspace(ymin, ymax, 100))
    pred = self.predict(np.c_[xx.ravel(), yy.ravel()])
    cmap_light = ListedColormap(['#FFAAAA', '#AAFFAA'])
    cmap_bold = ListedColormap(['#FF0000', '#00FF00']) 
    pred = pred.reshape(xx.shape)
    plt.figure() 
    print(xx.shape, yy.shape, pred.shape)
    plt.pcolormesh(xx, yy, pred, cmap=cmap_light)
    # Plot also the training points
    plt.scatter(X[:, 0], X[:, 1], c = y, cmap=cmap_bold)
    plt.xlim(xx.min(), xx.max())
    plt.ylim(yy.min(), yy.max())
    plt.title(str.format("{} Decision Boundary", self.kernel.__name__))
    plt.savefig(str.format("{} Decision Boundary.pdf", self.kernel.__name__))
  
  def predict(self, X):
    return np.array([self.hypothesis(x) for x in X])
  
  def crossValidate(self, X, y, k = 10):
    m = len(X)
    # Split into k folds
    folds = []
    for i in range(k):
      folds.append((X[i*m//k:(i+1)*m//k], y[i*m//k:(i+1)*m//k]))
    # Train on k-1 folds, test on 1 fold
    errors = []
    for i in range(k):
      X_train, y_train = [], []
      for j in range(k):
        if i != j:
          X_train.extend(folds[j][0])
          y_train.extend(folds[j][1])
      self.fit(np.array(X_train), np.array(y_train))
      errors.append(self._Error(folds[i][0], folds[i][1]))
    return sum(errors) / len(errors)
  
  def _Error(self, X, y):
    return np.sum(self.predict(X) != y) / len(y)