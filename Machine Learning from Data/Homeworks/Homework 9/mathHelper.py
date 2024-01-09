import numpy as np
  
def linRegErr(w, X, y):
  sum = 0
  wt = np.transpose(w)
  for i in range(len(X)):  
    sum+= np.power(np.matmul(wt, X[i]) - y[i], 2)
  return sum/len(X)

def linRegCVErr(X, y, reg_param):
  Xt = np.transpose(X)
  H_hat = np.matmul(X, np.matmul(np.linalg.inv(np.matmul(Xt, X) + reg_param * np.identity(X.shape[1])), Xt))
  y_hat = np.matmul(H_hat, y)
  sum = 0
  for i in range(len(X)):
    sum+= np.power((y_hat[i] - y[i])/(1-H_hat[i][i]), 2)
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

def linearRegression(X, y, reg_lambda = 0, doPocket = False):
  # returns the separator w = [bias, w1, w2]
  #print(str.format("X: {0}, y: {1}", X.shape, y.shape))
  if reg_lambda > 0:
    Xt = np.transpose(X)
    t1 = np.linalg.inv(np.matmul(Xt,X) + reg_lambda * np.identity(X.shape[1]))
    t2 = np.matmul(Xt, y)
    w_lin = np.matmul(t1, t2)
  else:  
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
  ret = np.array([                    \
    [1, X[i][1],                      \
    X[i][2], X[i][1]**2,              \
    X[i][1]*X[i][2], X[i][2]**2,      \
    X[i][1]**3, X[i][1]**2 * X[i][2], \
    X[i][2]**2 * X[i][1], X[i][2]**3] \
    for i in range(len(X))])
  return ret
 
def polyTransform(X, deg = 8, doLegendre = True):
  offset = 1 if len(X[0]) == 3 else 0
  transformed = []
  for i in range(len(X)):
    transformed.append([])
    if doLegendre:
      Lx1 = recLegPoly(deg, X[i][0+offset])
      Lx2 = recLegPoly(deg, X[i][1+offset])
    for j in range(deg+1):
      for k in range(deg+1):
        if j+k <= deg:
          if doLegendre:
            transformed[i].append(Lx1[j]*Lx2[k])
          else:
            transformed[i].append(X[i][0+offset]**j * X[i][1+offset]**k)
  return np.array(transformed)

def recLegPoly(degree, x):
  # Returns L_{0}(x), L_{1}(x), ..., L_{degree}(x)
  L0, L1 = 1, x
  if degree < 0:
    raise ValueError("The order of Legendre polynomial can't be negative")
  
  if degree == 0:
    return [L0]
  elif degree == 1:
    return [L0, L1]

  Ls = [L0, L1]
  Lkm1, Lkm2 = L1, L0
  for k in range(2, degree+1):
    Lk = (2*k-1)*x*Lkm1/k - (k-1)*Lkm2/k
    Ls.append(Lk)
    Lkm2 = Lkm1
    Lkm1 = Lk
  return Ls



    