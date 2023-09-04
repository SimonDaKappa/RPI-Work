
def find_min_subsets(S, n):
  remaining_elm = set(range(1,n+1))
  select_subsets = []
  
  while remaining_elm:
    best_sub = None
    max_intersection = 0
    
    for subset in S:
      inters = subset.intersection(remaining_elm)
      length = len(inters)
      
      if length >= max_intersection:
        best_sub = subset
        max_intersection = length  

    select_subsets.append(best_sub)
    remaining_elm -= set(best_sub)
    
  return select_subsets

if __name__ == "__main__":
  """
  PART A
  """
  
  S=set([
    frozenset([1,3,5,7,10,11]),
    frozenset([1,2,4,5,11]),
    frozenset([4,8,9]),
    frozenset([1,3,5,8,9,10]),
    frozenset([2,6,10])
    ])
  
  print(str.format("Sets = {}", S))
  A = find_min_subsets(S, 11)
  print(str.format("Subsets = {}", A))
  """
  PART B
  O(nk), where n = number of elements to be covered, k = number of subsets
  
  The outer loop runs at most n times, and in worst-case, the inner loop must run
  for the last subset every single iteration, k times.
  
  """
  """
  PART C
  
  This problem falls in the /alpha = log(n) class
  """