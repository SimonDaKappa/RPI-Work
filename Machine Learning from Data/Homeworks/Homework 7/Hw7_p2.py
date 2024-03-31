import numpy as np
import matplotlib.pyplot as plt

def grad(x,y):
  return np.array([2*x+4*np.pi * np.sin(2*np.pi*x)*np.sin(2*np.pi*y), 4*y+4*np.pi * np.sin(2*np.pi*y)*np.sin(2*np.pi*x) ])

def func(x,y):
  return x**2 + 2*y**2 + 2 * np.sin(2*np.pi*x)*np.sin(2*np.pi*y)

def gradDescent(x: np.ndarray, eta: float, iter: int):
  fvals, iters = [], []
  for _iter in range(iter):
    x = x - eta * grad(x[0], x[1])
    fvals.append(func(x[0], x[1]))
    iters.append(_iter)
    if np.linalg.norm(grad(x[0], x[1])) < 0.0001:
      break
  return x, fvals, iters

if __name__ == "__main__":
  starts = np.array([[0.1, 0.1],[1,1],[-0.5,-0.5],[-1,-1]])
  plt.figure()
  plt.title("Grad Descent with multiple starting points")
  plt.xlabel("Iteration")
  plt.ylabel("f(x)")
  for i in range(len(starts)):
  #for i in range(0,1):
    x_opt, fvals, iters = gradDescent(starts[i], 0.01, 50)
    #print(str.format("start = {}, x_opt = {}", starts[i], x_opt))
    plt.plot(iters, fvals, label = str.format("Start = {}", starts[i]))
    
    #x_opt, fvals, iters = gradDescent(starts[i], 0.1, 50)
    print(str.format("start = {}, x_opt = {}, val = {}", starts[i], x_opt, func(x_opt[0], x_opt[1])))
    #plt.plot(iters, fvals, label = str.format("Eta = {}", 0.1))
    
  plt.legend()
  plt.savefig("Hw7_p2_eta_comp.pdf")