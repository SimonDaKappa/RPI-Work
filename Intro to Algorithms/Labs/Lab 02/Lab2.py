import time
import sys
import random
import math

def method1(m,n):
  num2 = bin(n)
  ans = 0
  for i in range(len(num2)):
    if num2[i] == "1":
      ans += m << i
  return ans
      
def method2(x,y):
  if y == 0:
    return 0
  
  z = method2(x, y >> 1) #floor(y/2)
  if y % 2 == 0:
    return z << 1 # 2z
  else:
    return x + (z << 1) # x + 2z
      
def method3(x,y):
  n = max(x.bit_length(),y.bit_length())
  if n == 1:
    return x*y
  if x == 0 or y == 0:
    return 0
  num_shift = math.floor(n/2)
  
  xL = x >> num_shift
  m = xL << num_shift
  xR = x - m
  
  yL = y >> num_shift
  m = yL << num_shift
  yR = y - m
  
  p1 = method3(xL,yL)
  p2 = method3(xR,yR)
  p3 = method3(xL+xR,yL+yR)
  return p1 * (2**(2*num_shift)) + (p3-p1-p2) * (2**num_shift) + p2



if __name__ == "__main__":
  
  print(method1(17,20))
  d = int(input("Enter Decimal Count: "))
  
  t_tot = 0
  for i in range(10): # Over 10000
    n1 = random.randint(10**(d-1), 10**d-1)
    n2 = random.randint(10**(d-1), 10**d-1)
    t_run = time.time()
    res = method1(n1,n2)
    t_end = time.time()
    t_tot += (t_end - t_run)
   
  t_avg = t_tot/10
  print("\nAverage time for Method 1 with {}-digit num's is {:.5f} seconds".format(d, t_avg))
  
  t_tot = 0
  for i in range(10): # 300 ish digits (python max recursion depth is 1000 so why 300??)
    n1 = random.randint(10**(d-1),10**d-1)
    n2 = random.randint(10**(d-1),10**d-1)
    t_run = time.time()
    res = method2(n1,n2)
    t_end = time.time()
    
    t_tot += (t_end - t_run)
    
  t_avg = t_tot/10
  print("\nAverage time for Method 2 with {}-digit num's is {:.5f} seconds".format(d, t_avg))
  
  t_tot = 0
  for i in range(10): #300 ish digits 
    n1 = random.randint(10**(d-1),10**d-1)
    n2 = random.randint(10**(d-1),10**d-1)
    t_run = time.time()
    res = method3(n1,n2)
    t_end = time.time()
    
    t_tot += (t_end - t_run)
    
  t_avg = t_tot/10
  print("\nAverage time for Method 3 with {}-digit num's is {:.5f} seconds".format(d, t_avg))
  