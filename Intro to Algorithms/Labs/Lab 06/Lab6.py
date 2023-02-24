
from collections import deque

def readGraph(fname, vertex_count = 0):
  # Read in the graph to adjacent list format
  #fname = input("Enter the file name: ")
  file = open(fname, "r")
  AdjacencyList = dict()
  while(True):
    line = file.readline()
    if not line:
      break
    lineArr = line.split()
    vertex_count = max(vertex_count, int(lineArr[0]), int(lineArr[1]))
    if AdjacencyList.get(int(lineArr[0])) == None:
      AdjacencyList[int(lineArr[0])] = list()
    AdjacencyList[int(lineArr[0])].append(int(lineArr[1]))
    #print(line)
  return AdjacencyList, vertex_count


def reverseGraph(AdjacencyList):
  # Reverse the graph in |E| time
  #print(AdjacencyList)
  reverseAdjacency = dict()
  for i in AdjacencyList.keys():
    for j in range(0,len(AdjacencyList[i])):
      if reverseAdjacency.get(AdjacencyList[i][j]) == None:
        reverseAdjacency[AdjacencyList[i][j]] = [i]
      else:
        reverseAdjacency[AdjacencyList[i][j]].append(i)
  return reverseAdjacency
  
def postVisit(v):
  post.append(v)   
    
def Explore(AdjacencyList, v, visited):
  # Visit a vertex in DFS
  visited[v] = True
  if AdjacencyList.get(v) != None:
    for u in AdjacencyList[v]:
      if not visited[u]:
        Explore(AdjacencyList, u, visited)
  postVisit(v)

def depthFirstSearch(AdjacencyList):
  # Perform a depth first search on the graph
  visited = [False] * (vertex_count+1)
  print(str.format("len visited = {}",len(visited)))
  print(str.format("Visited ={}",visited))
  for v in AdjacencyList.keys():
    print(v)
    visited[v] = False   
  for v in AdjacencyList.keys():
    if not visited[v]:
      Explore(AdjacencyList, v, visited) 

def Explore2(AdjacencyList, v, visited, v_visited):
  # Visit a vertex in DFS
  if visited[v] or v_visited[v]:
    return
  v_visited[v] = True
  visited[v] = True
  if AdjacencyList.get(v) != None:
    for u in AdjacencyList[v]:
      if not v_visited[u]:
        Explore2(AdjacencyList, u, visited, v_visited)
  
def DFS2(AdjacencyList, u, visited):

  #print(len(visited))
  print(str.format("DFS2({}, visited)",u))
  if not visited[u]:
    u_visited = [False] * (vertex_count+1)
    # Do DFS on all reachable vertices from u
    Explore2(AdjacencyList, u, visited, u_visited)
    # If reached, add to connected component list
    for v in range(len(u_visited)):
      if u_visited[v]:
        print(str.format("Adding {} to ccList[{}]",v,u))
        ccList[u].append(v)
        #print(str.format("cclist = {}",ccList))
        print(str.format("ccList[{}] = {}",u,ccList[u]))


if __name__ == "__main__":
  # Read in the graph to adjacent list format
  #fname = input("Enter the file name: ")
  #fname = "Example.txt"
  fname = "LAB6-TEST-SET.txt"
  AdjacencyList, vertex_count = readGraph(fname)
  print(AdjacencyList)
  reverseAdjacency = reverseGraph(AdjacencyList)
  print(reverseAdjacency)
  cc     = 0
  ccList = [ [] for i in range(vertex_count+1)]
  print(str.format("ccList = {}",ccList))
  post   = []
  
  # Do DFS to calculate post order
  depthFirstSearch(reverseAdjacency)
  print(str.format("Post order = {}",post))
  # Iterate through post order 
  visited = [False] * (vertex_count+1)
  for i in range(len(post) - 1, 0, -1):
    u = post[i] 
    # Do DFS on all reachable vertices from u
    DFS2(AdjacencyList, u, visited)
  # Print the connected components
  
  for i in range(len(ccList) -1, 0, -1):
    if not visited[i]:
      print(i)
    for j in range(0,len(ccList[i])):
      print(ccList[i][j], end = ' ')
    if ccList[i] != None:
      print()
    
    
    
    
    
  
    
