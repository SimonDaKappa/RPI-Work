import sys
import math
import random


def modexp(x , y , N):
  """Compute (x^y) mod N"""
  if y == 0: 
    return 1
  z = modexp(x, y >> 1 , N)
  if y % 2 == 0:
    return (z * z) % N
  else:
    return  x * (z * z) % N

def primality2(N, k):
  #random_list = [random.randint(1, N-1) for i in range(k)]
  count = 0;
  for i in range(k):
    random_num = random.randint(1, N-1)
    if modexp(random_num, N-1, N) == 1: # If wrongly decided prime add to count
      count += 1 
  print(str.format("{} Is Not Prime | Probability of Failure is {}", N, count / k)) 
  return count / k    
  

if __name__ == "__main__":
  print(modexp(6,25,40))
  print(modexp(3,3,4))
  
  carmichael_num = [561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041, 46657, 52633, 62745, 63973, 75361, 101101, 115921, 126217, 162401, 172081, 188461, 252601, 278545, 294409, 314821, 334153, 340561, 399001, 410041, 449065, 488881]
  tot_prob = 0
  for num in carmichael_num:
    tot_prob += primality2(num, 1000)
  print(str.format("Average Probability: {} >> {}", tot_prob/len(carmichael_num), 1 / (2 ** 1000)))