
import time
import sys
import random


def randSelection(S: list, k: int) -> int:
  print(str.format("len(S) = {}\n",len(S)))
  if len(S) <= 1:
    return S[0]
  v_i = random.randint(0, len(S) - 1)
  v = S[v_i]
  
  Sl = list(filter(lambda x: x < v, S))
  Sv = list(filter(lambda x: x == v, S))
  Sr = list(filter(lambda x: x > v, S))
  
  lenSl = len(Sl)
  lenSv = len(Sv)
  
  if k <= lenSl:
    return randSelection(Sl, k)
  elif lenSl < k and k <= lenSl + lenSv:
    return v 
  elif k > lenSl + lenSv:
    return randSelection(Sr, k - lenSl - lenSv)
 


if __name__ == "__main__":
  n = int(input("Enter n: "))
  ranArr = list(random.randint(0,n) for i in range(n))
  print(str.format("Random Array = {}\n",ranArr))
  k = int(input("Enter k: "))
  print(str.format("Select {}-th integer = {}\n",k, randSelection(ranArr,k)))
  print(str.format("Sorted Array = {}\n",sorted(ranArr)))
  print(str.format("Select {}-th integer = {}\n",k, sorted(ranArr)[k-1]))
        