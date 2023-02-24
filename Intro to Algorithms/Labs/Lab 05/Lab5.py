import random

def randQuickSort(S : list):
  return randQuickSortHelper(S, 0, len(S) - 1)  

def randQuickSortHelper(S : list, start: int, stop: int):
  if(start < stop):
    pivot = partitionRandom(S, start, stop)
    randQuickSortHelper(S, start, pivot)
    randQuickSortHelper(S, pivot + 1, stop)

def partitionRandom(S : list, start: int, stop: int) -> int:
  """ Select Random pivot and swap with start-th element in list.
      Then partition according to random pivot.
  """
  pivotRand = random.randrange(start, stop)
  S[start], S[pivotRand] = S[pivotRand], S[start]
  return partition(S, start, stop) 

def partition(S : list, start: int, stop: int) -> int:
  """ Partition the list S[start:stop+1] so that all elements 
      before the pivot are less than or equal to the pivot, 
      and all elements after the pivot are greater than 
      or equal to the pivot. Return the index of the pivot.  
  """
  pivot = start
  i = start - 1
  j = stop + 1
  while True:
      while True:
          i = i + 1
          if S[i] >= S[pivot]:
              break
      while True:
          j = j - 1
          if S[j] <= S[pivot]:
              break
      if i >= j:
          return j
      S[i] , S[j] = S[j] , S[i]
      
if __name__ == "__main__":
  n = int(input("Enter n: "))
  multiplier = int(input("Enter random multiplier: "))
  ranArr = list(random.randint(0,random.randint(1,multiplier)*n) for i in range(n))
  print(str.format("Random Array = {}\n",ranArr))
  randQuickSort(ranArr)
  print(str.format("Sorted Array = {}\n",ranArr))
  sorted = all(ranArr[i] <= ranArr[i+1] for i in range(len(ranArr) - 1))
  print(str.format("List is sorted: {}",sorted))