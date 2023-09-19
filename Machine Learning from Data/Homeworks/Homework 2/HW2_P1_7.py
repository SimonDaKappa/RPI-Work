import matplotlib.pyplot as plt
import numpy as np

def hoeffding(epsilon, N):
    return 2*np.exp(-2*epsilon*epsilon*N)
  
def coinProb(N, epsilon_list, mu):
  k = np.random.binomial(n = N,p =  mu, size = (1000, 1))
  P = np.abs(k/N-mu).max(axis = 1)
  return [(P > epsilon).mean() for epsilon in epsilon_list]

if __name__ == "__main__":
  N = 6
  M = 2
  mu = 0.5
  epsilon_list = np.linspace(0, 1, 100)
  plt.figure()  
  plt.plot(epsilon_list, hoeffding(epsilon_list, 6), label = "Hoeff | N = 6")
  plt.plot(epsilon_list, hoeffding(epsilon_list, 2), label = "Hoeff | N = 2")
  plt.plot(epsilon_list, coinProb(6, epsilon_list, mu), label ="coinProb | N = 6")
  plt.plot(epsilon_list, coinProb(2, epsilon_list, mu), label ="coinProb | N = 2")
  plt.title("Problem 1.7")
  plt.legend()
  plt.show()
  plt.savefig("HW2_P1_7.pdf")