from heapdict import heapdict
from collections import deque
def read_graph(filename):
    V = []
    E = dict()
    L = []
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip().split()
            if line == []:
                continue
            if int(line[0]) not in V:  
              V.append(int(line[0]))
            if int(line[1]) not in V:  
              V.append(int(line[1]))
            if int(line[0]) not in E:
              E[int(line[0])] = [(int(line[1]), int(line[2]))]
            else: 
              E[int(line[0])].append((int(line[1]), int(line[2]))) # Add u -> (v,l_uv) to dict
    return V, E

def dijkstras(V, E, s):
  # Create dist,prev arrays
  dist = [float('inf')]
  prev = [0]
  for u in V:
    dist.append(float('inf'))
    prev.append(None)
  dist[s] = 0
  # Make the priority queue with dist as the key
  H = heapdict()
  for u in V:
    H[u] = dist[u]
  
  while H:
    u = H.popitem()[0]
    if E.get(u) == None:
      continue
    for v,l in E[u]:
      alt = dist[u] + l
      if dist[v] > alt:
        dist[v] = alt
        prev[v] = u
        H[v] = alt
  return prev, dist

if __name__ == "__main__":
  fname = input("Enter the name of the graph file: ")
  V,E = read_graph(fname)  
  source = 1
  prev,dist = dijkstras(V,E,source)
  for i in range(1,len(prev)):
    print("Shortest path from",source,"to",i,"is:",end=' ')
    st = deque()
    while i != None:
      st.appendleft(i)
      i = prev[i]
    print(len(st),end=' ')
    print(list(st))
    