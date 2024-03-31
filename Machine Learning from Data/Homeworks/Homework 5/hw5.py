import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
  N_X = 1000
  N_data = 1000
  X = np.random.uniform(-1,1,(N_X,2))
  x_1 = [x_i[0] for x_i in X]
  x_2 = [x_i[1] for x_i in X]
  a = [x_i[0]+x_i[1] for x_i in X] 
  b = [-x_i[0]*x_i[1] for x_i in X]
  a_bar = np.mean(a)
  b_bar = np.mean(b)
  data = np.linspace(-1,1,N_data)
  gbar_data = a_bar*data-b_bar
  print(gbar_data)
  f_data = data**2
  gd_a = [a_i * data for a_i in a]
  gd_b = [b_i * data for b_i in b]
  gd = np.subtract(gd_a,gd_b)
  var = np.mean(np.subtract(gd,gbar_data)**2)
  print(str.format("Variance = {}\n",var))
  bias = np.mean(np.subtract(gbar_data,f_data)**2)
  print(str.format("Bias = {}\n",bias))
  print(str.format("Eout = {}\n",bias+var))

  plt.plot(data, gbar_data, linewidth = 4, label = "gbar(x)")
  plt.plot(data, f_data, linewidth = 4, label = "f(x) = x^2")
  #for gd_i in gd:
  #  plt.plot(data, gd_i,alpha= 0.05)
  plt.legend()
  plt.xlim =(-1,1)
  plt.ylim(-0.1,1)
  plt.savefig("Hw5Plot.png")
    
    
  #print(X)
  #print(a)
  #print(b)
  #print(a_bar)
  #print(b_bar)