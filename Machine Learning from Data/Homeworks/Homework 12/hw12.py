import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
import numpy as np
from Hw9 import *
from NeuralNetwork import *
from SupportVectorMachine import *
import time

def testkernel(x1, x2):
  return np.dot([x1[0]**3-x1[1]], [x2[0]**3-x2[1]])

def poly8kernel(x1, x2):
  return (1 + np.dot(x1, x2))**8

if __name__ == "__main__":
  
  #NN = NeuralNetwork([2,2,1], np.tanh, np.tanh, perturb = False)
  #NN.fit([[2,1]],[-1])
  #NN = NeuralNetwork([2, 3, 3, 1], np.tanh, np.tanh, perturb = True)
  #t1 = time.time()
  #NN.fit(np.array([[2,1], [1,-2], [1.5,-1], [2,2]]), np.array([-1, 1, 1, -1]),weight_penalty=0.0, learn_rate = 0.01, iterations = 1000,  grad_modes = ["batch"], early_stop = False, plot_boundary = True)
  # tbatch = time.time() - t1
  #NN.fit([[2,1]],[-1], weight_penalty=0.0, learn_rate = 0.01, iterations = 10, grad_modes = ["stochastic"])
  # tschoc = time.time() - t1 - tbatch
  # print("Batch: " + str(tbatch))
  # print("\nStochastic: " + str(tschoc))
  # print(NN.predict([[2,1]]))
  
  labels = [1,2,3,4,5,6,7,8,9]
  path_train, path_test = "zip.train", "zip.test"
  Data, Labels = createData(path_train, labels, includeBias = False)
  Data_test, Labels_test = createData(path_test, labels, includeBias = False)
  Data, Labels = np.concatenate((Data, Data_test)), np.concatenate((Labels, Labels_test))
  
  # Separate 300 random points from into train set
  #train_idxs = np.random.choice(len(Data), 300, replace = False)
  train_idxs = np.linspace(0,len(Data)-1, 300, dtype=int)
  print(train_idxs)
  Data_train, Labels_train = Data[train_idxs], Labels[train_idxs]
  test_idxs = np.delete(np.array([i for i in range(len(Data))]), train_idxs)
  Data_test, Labels_test = Data[test_idxs], Labels[test_idxs]
  
  NN = NeuralNetwork([2,10,1], np.tanh, np.tanh, perturb = True)
  learn_rate, iterations, error_samples  = .1, 2 * int(1e6), 100
  grad_modes, early_stop = ["stochastic"], True
  plot_boundary, plot_errors, verbose = True, True, False
  batch_size, weight_penalty = 10, 0.0
  ret = NN.fit(Data_train, Labels_train, learn_rate = learn_rate, iterations = iterations, error_samples = error_samples, batch_size = batch_size, grad_modes = grad_modes, early_stop = early_stop, plot_boundary = plot_boundary, verbose = verbose, weight_penalty = weight_penalty, plot_errors = plot_errors)
  print(str.format("Min error: {}, idx: {}", min(ret[0]), np.argmin(ret[0]))) 
  #SVM = SupportVectorMachine(testkernel, 1e12)
  # C = np.logspace(-5, 5, 25)
  # # C = [1e-2]
  # #C = [10]
  
  # Error_CV, Error_test = [], []
  # for c in C:
  #   SVM = SupportVectorMachine(poly8kernel, C = c)
  #   Error_CV.append(SVM.crossValidate(Data_train, Labels_train, 5))
  #   Error_test.append(SVM._Error(Data_test, Labels_test))
  #   print(str.format("C: {}\n train cv error: {}, test error: {}", c, Error_CV[-1], Error_test[-1]))
  # train_mindex, test_mindex = np.argmin(Error_CV), np.argmin(Error_test)
  # print(str.format("Min train error: {}, idx: {}", Error_CV[train_mindex], train_mindex))
  # SVM = SupportVectorMachine(poly8kernel, C = C[train_mindex])
  # SVM.fit(Data_train, Labels_train)
  # SVM.plotDecisionBoundary(Data_train, Labels_train)
  # plt.figure()
  # plt.plot(C, Error_CV, label = "CV Error")
  # plt.plot(C, Error_test, label = "Test Error")
  # plt.legend()
  # plt.xscale("log")
  # plt.savefig("CV Error.pdf")
  