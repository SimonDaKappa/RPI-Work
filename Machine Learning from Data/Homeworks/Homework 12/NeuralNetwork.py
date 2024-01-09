import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import time

class NeuralNetwork:
  def __init__(self, dimensions, hiddenTransform, outputTransform, perturb = True):
    self.dimensions = dimensions
    self.hiddenTransform = hiddenTransform
    self.outputTransform = outputTransform
    self.Weights = []
    for i in range(len(dimensions) - 1):
      self.Weights.append(np.array([[0.0 for _ in range(dimensions[i] + 1)] for _ in range(dimensions[i + 1])]))
      #self.Weights.append(np.random.randn(dimensions[i + 1], dimensions[i] + 1))
    if perturb:
      for i in range(len(dimensions) - 1):
        for j in range(dimensions[i + 1]):
          for k in range(dimensions[i] + 1):
            self.Weights[i][j][k] += np.random.normal(0, 0.15)
    print(str.format("Weights: {0}\n",self.Weights))
  
  def predict(self, X):
    out = []
    for x in X:
      activations_ff = self.feedForward(x)[0]
      out.append(np.sign(activations_ff[-1][1]))
    return np.array(out)
  
  def feedForward(self, x):
    S_ff = [np.array([])]
    X_ff = [self._prependOne(x)]
    for i in range(1,len(self.dimensions)):
      S_ff.append(self.Weights[i-1] @ X_ff[i-1])
      tmp = self._prependOne(self.hiddenTransform(S_ff[i])) 
      X_ff.append(tmp)
    # Output
    return X_ff, S_ff
  
  def fit(self, X, y, weight_penalty = 0.0, learn_rate = 0.01, 
          iterations = 1, error_samples = 1, batch_size = 1,
          grad_modes = ["batch"], early_stop = False,
          plot_boundary = False, plot_errors = False, verbose = False):
    
    # Init
    ret = []
    l_rate = learn_rate / len(X)

    if "stochastic" in grad_modes:
      error_samples = iterations // len(X)
      print(str.format("Error Samples: {0}", error_samples))
    Errors = np.zeros(error_samples)
    weight_penalty /= len(X)
    
    if early_stop:
      verif_idx = np.random.choice(len(X), len(X)//6, replace = False)
      X_verif = [X[i] for i in verif_idx]
      Y_verif = [y[i] for i in verif_idx]
      X = np.delete(X, verif_idx, axis = 0)
      y = np.delete(y, verif_idx, axis = 0)
      Weights_History, Errors_Verif = [], []
      NN_Verif = NeuralNetwork(self.dimensions, self.hiddenTransform, self.outputTransform, perturb = False)

    error_idx = 0
    percent = 0
    avg_error = 0
    for _iter in range(iterations):
      if _iter % (iterations // 10) == 0:
        print(str.format("Iteration: ({0} of {1}, {2}% Done", _iter, iterations, percent))
        print("Average Error over last 10%: " + str(avg_error / (error_samples // 10)))
        percent += 10
        avg_error = 0        

      # Init gradients
      gradients = [np.multiply(0, self.Weights[i]) for i in range(len(self.dimensions) - 1)]
      
      if "stochastic" in grad_modes:
        # Choose a single point from the dataset  
        idx = np.random.choice(len(X), 1, replace = False)[0]
        X_iter = [X[idx]]
        y_iter = [y[idx]]
      elif "minibatch" in grad_modes:
        # Choose a minibatch of 20 points from the dataset  
        idx = np.random.choice(len(X), batch_size, replace = False)
        X_iter = [X[i] for i in idx]
        y_iter = [y[i] for i in idx]
      elif "batch" in grad_modes:
        X_iter = X
        y_iter = y
      else: 
        exit(str.format("Invalid grad_mode: {0}, Use 'stochastic', 'batch', 'minibatch', and 'adaptive'", grad_modes))
        
      for i in range(len(X_iter)):     
        activations_Xi, signals_Xi = self.feedForward(X_iter[i])
        sensitivities_Xi = self.backpropagate(y_iter[i], activations_Xi, signals_Xi)
        #print(str.format("Sensitivities: {0}", sensitivities_Xi))
          
          
          
        # Gradients
        for l in range(1, len(self.dimensions)):
          act_li = np.array([activations_Xi[l-1]])
          sens_li = np.array([sensitivities_Xi[l]])
          grad_l = act_li.T @ sens_li
          gradients[l-1] += grad_l.T
      if verbose:
        print(str.format("Gradients: {0}", gradients))
      
      # Update Weights
      if "batch" in grad_modes or "minibatch" in grad_modes:
        if "adaptive" in grad_modes:
          l_rate = self.gradDescStepAdaptive(X_iter, y_iter, gradients, weight_penalty = weight_penalty, l_rate = l_rate)
        else:
          self.gradDescStep(X_iter, y_iter, gradients, weight_penalty = weight_penalty, l_rate = l_rate) 
      elif "stochastic" in grad_modes:
        self.gradDescStep(X_iter, y_iter, gradients, weight_penalty = weight_penalty, l_rate = l_rate)
       
      if _iter % (iterations // error_samples) == 0 and error_idx < error_samples:
        error_iter = self._Error(X, y)
        Errors[error_idx] = error_iter
        error_idx += 1
        avg_error += error_iter
        if verbose:
          print(str.format("Iter: {0}, Error: {1}", _iter, error_iter))
          if "adaptive" in grad_modes:
            print(str.format("l_rate: {0}", l_rate)) 
       
      if early_stop and _iter % (iterations // error_samples) == 0 and error_idx <= error_samples:
        Weights_History.append(self.Weights)
        NN_Verif.Weights = self.Weights
        Errors_Verif.append(NN_Verif._Error(X_verif, Y_verif))
    
    ret.append(Errors) 
    
    if early_stop: 
      verif_mindex = np.argmin(Errors_Verif)
      self.Weights = Weights_History[verif_mindex]
      if plot_boundary:
        self.plotDecisionBoundary(X, y, grad_modes = grad_modes, early_stop = early_stop, verif_mindex = verif_mindex, weight_penalty = weight_penalty)
      print(str.format(
        "Early Stop: Iteration {0}, Error {1}",
        verif_mindex * (iterations //  error_samples),
        Errors_Verif[verif_mindex]))
      
      ret.append(Errors_Verif)
    
    if plot_boundary and not early_stop:
      self.plotDecisionBoundary(X, y, grad_modes = grad_modes, weight_penalty = weight_penalty)       
    
    if plot_errors:
      self.plotErrors(X, ret, iterations, grad_modes = grad_modes, early_stop = early_stop, weight_penalty = weight_penalty) 
      
    return ret 
  
  def plotErrors(self,X,  errors, iterations, grad_modes = None, early_stop = False, weight_penalty = 0.0):
    plt.figure()
    
    print(str.format("Errors: {0}", errors[0]))
    print(str.format("Iterations: {0}", iterations))
    plt.ylabel("Error")
    title, path = "", ""
    
    if "stochastic" in grad_modes:
      print(len(errors[0]))
      print(iterations // len(X))
      plt.plot(np.linspace(0, iterations / len(X), len(errors[0])), errors[0], label = "Train Set Error")
      plt.xlabel(str.format("Iterations / {0}", len(X)))
      if early_stop:
        print(len(errors[1]))
        plt.plot(np.linspace(0, iterations / len(X), len(errors[1])), errors[1], label = "Verification Set Error")
        verif_mindex = np.argmin(errors[1])
        plt.plot(verif_mindex, np.min(errors[1]), 'ro')
        plt.legend()
        title += "Verif Mindex: " + str(verif_mindex) + "\n"
        path += "EarlyStop "
      
    else:
      plt.plot(range(0, iterations, iterations // len(errors[0])), errors[0], label = "Train Set Error")
      plt.xlabel("Iterations")
      if early_stop:
        plt.plot(range(0, iterations, iterations // len(errors[1])), errors[1], label = "Verification Set Error")
        # Plot the minimum value of the early stop
        verif_mindex = np.argmin(errors[1])
        plt.plot(verif_mindex * (iterations // len(errors[1])), errors[1][verif_mindex], 'ro')
        plt.legend()
        title += "Verif Mindex: " + str(verif_mindex) + "\n"
        path += "EarlyStop "

    plt.title(title + str.format("Error vs Iterations for {} Gradient Descent", grad_modes))
    plt.savefig(path + str.format("Error vs Iterations for {}.pdf", grad_modes))
      
      
        
  def plotDecisionBoundary(self, X, y, grad_modes = None,
    early_stop = False, verif_mindex = 0,
    weight_penalty = 0.0):
    
    xmin, xmax = np.min(X[:,0]), np.max(X[:,0])
    ymin, ymax = np.min(X[:,1]), np.max(X[:,1])
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
    title, path = "", ""
    if early_stop:
      title += "Verif Mindex: " + str(verif_mindex) + "\n"
      path += "EarlyStop "
    if weight_penalty > 0.0:
      title += "Weight Penalty: " + str(weight_penalty) + "\n"
      path += "WeightPenalty "
    plt.title(title + str.format("Decision Boundary for {}", grad_modes))
    plt.savefig(path + str.format("Decision Boundary for {}.pdf", grad_modes))    
      
  def gradDescStep(self, X, y, gradients, weight_penalty = 0.0, l_rate = 0.01):
    for l in range(len(self.dimensions) - 1):
      self.Weights[l] -= l_rate * ( gradients[l] + (2 * weight_penalty * self.Weights[l] / len(X)))

  def gradDescStepAdaptive(self, X, y, gradients, weight_penalty = 0.0, 
                           l_rate = 0.01, alpha = 1.1, beta = 0.8):
    if l_rate < 1e-10:
      return .1
    
    eta = l_rate 
    error_old = self._Error(X, y)
    weights_tmp = self.Weights
    
    for l in range(len(self.dimensions) - 1):
      self.Weights[l] -= eta * ( gradients[l] + 2 * weight_penalty * self.Weights[l] / len(X))
      
    error_new = self._Error(X, y)
    #print(str.format("Error_old: {0}, Error_new: {1}", error_old, error_new))
    if error_new < error_old:
      #print(str.format("Accept: eta = "), alpha*eta)
      # ACCEPT - Weights already updated
      eta *= alpha
    else:
      #print(str.format("Reject: eta = "), beta*eta)
      # REJECT - Reset weights
      self.Weights = weights_tmp
      eta *= beta
    return eta    
   
  def backpropagate(self, y, activations, signals):
    sensitivities = [2*(activations[-1][1] - y) * self.phiPrime2(activations[-1])]
    for i in range(len(self.dimensions) - 2, 0, -1):
      phiPrime_i = self.phiPrime2(activations[i])
      sensitivity =  np.multiply((self.Weights[i].T @ sensitivities[-1])[1:], phiPrime_i)
      sensitivities.append(sensitivity)
    sensitivities.append(np.array([]))
    sensitivities = list(reversed(sensitivities))
    return sensitivities
  
  def phiPrime2(self, x):
    return (1 - np.square(x)[1:])
  
  def _prependOne(self, X : np.array):
    # Below is VERY SLOWWWW
    # return np.insert(X, 0, 1)
    # So instead preallocate array and populate
    tmp = np.empty(len(X) + 1)
    tmp[0], tmp[1:] = 1, X
    return tmp    
      
  def _Error(self, X, y):
    error = 0
    for i in range(len(X)):
      activations_Xi, _ = self.feedForward(X[i])
      error += (1/len(X)) * (activations_Xi[-1][1] - y[i])**2
    return error   
  