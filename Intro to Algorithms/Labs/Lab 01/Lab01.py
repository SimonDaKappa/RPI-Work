import sys
import time
import matplotlib.pyplot as plt

def fib(n):
  if n == 0:
    return 0
  if n == 1:
    return 1
  return fib(n-1) + fib (n-2)  

def fib2(n):
  if n == 0:
    return 0
  arr = list(range(0,n))
  arr[0] = 0
  arr[1] = 1
  for i in range(2,n):
    arr[i] = arr[i - 1] + arr[i - 2]
  return arr[n-1]

def timefib(nlist):
  timelist = list()
  time2list = list()
  for i in range(len(nlist)):
    t1 = time.time()
    res = fib(nlist[i])
    t2 = time.time()
    timedif = t2-t1
    timelist.append(timedif)
    
    t1 = time.time()
    res = fib2(nlist[i]+1)
    t2 = time.time()
    timedif = t2-t1
    time2list.append(timedif)
  print(timelist)
  print(time2list)
  plt.plot(nlist,timelist,label = "fib 1")
  plt.plot(nlist,time2list,label = "fib 2")
  plt.legend()
  plt.show()
    
def timefib2(nlist):
  timelist=list()
  for i in range(len(nlist)):
    t1 = time.time()
    res = fib2(nlist[i]+1)
    t2 =time.time()
    timelist.append(t2-t1)
  print(timelist)
  plt.plot(nlist,timelist,label = "fib2", marker = ".")
  plt.show()


if __name__ == "__main__":
  n = int(sys.argv[1])
  t1 = time.time()
  res = fib(n)
  t2 = time.time()
  print("fib(n) = " + str(res))
  print("Fib time = " + str(t2-t1))
  
  t1 = time.time()
  res = fib2(n+1)
  t2 = time.time()
  print("fib2(n) = " + str(res))
  print("Fib2 time = " + str(t2-t1))
  
  nlist = [1, 5, 10, 15, 20, 25, 30, 35]#, 40, 41, 42 , 43]
  timefib(nlist)
  
  nlist = [2**10,2**12,2**14,2**16,2**18]
  timefib2(nlist)
  

  
  
  
