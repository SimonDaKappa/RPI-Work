def find_set(v, F):
  for i in range(len(F)):
    if v in F[i]:
      return i
  return -1

def merge_set(u, v, F):
  findu = find_set(u,F)
  findv = find_set(v,F)
  if findu != findv:
    F[findu] = F[findu].union(F[findv])
    F.pop(findv)
    
def is_spanning(V, F):
  print("F = ", F)
  print("V = ", V)
  # Do dfs to see if all nodes are reachable
  reached = dict()
  for u in V:
    #print(str.format("isspanning reached 1, u = {}",u))
    reached[u] = False
  print(reached)
  for u in V:
    if not reached[u] or u not in reached.keys():
      #print(str.format("Outer DFS Called on u = {}", u))
      DFS(V, F, u, reached)
  print(reached)
  for r in reached:
    if r == False:
      return False  
  if len(F) != len(V) - 1:
    return False  
  return True

def DFS(V, F, u, reached):
  reached[u] = True
  for u_,v,l in F:
    if v not in reached.keys():
      reached[v] = False 
    if u == u_ and not reached[v]:
      DFS(V, F, v, reached)
  
if __name__ == "__main__":
  #fname = input("Enter the name of the graph file: ")
  #,E = read_graph(fname) 
  V = {"A","B","C","D","E","F","G","H","I"}
  U = {"A", "E", "F"}
  #E={(A-B,10), (A-C,12), (B-C,9), (B-D,8), (C-E,3), (C-F,1), (D-E,7), (D-G,8), (D-H,5), (E-F, 3) (FH,6), (G,H,9), (G-I,2), (H-I,11)} 
  E = dict()
  E["A"] = [("B",10), ("C",12)]
  E["B"] = [("C",9), ("D",8)]
  E["C"] = [("E",3), ("F",1)]
  E["D"] = [("E",7), ("G",8), ("H",5)]
  E["E"] = [("F",3)]
  E["F"] = [("H",6)]
  E["G"] = [("H",9), ("I",2)]
  E["I"] = []
  E["H"] = [("I",11)]
  
  # Create V - U, E'
  V_U = V - U
  print(V_U)
  Ep = dict()
  for u in V_U:
    Ep[u] = []
    for v,l in E[u]:
      if v in V_U and l not in U:
        Ep[u].append((v,l))
  print(Ep)
  
  # Apply Kruskal's algorithm to E'
  # Order the edges in E' by weight
  Eprime = list()
  for u in Ep:
    for v,l in Ep[u]:
      Eprime.append((u,v,l))
  print(Eprime)
  #Sort Eprime by weight
  Eprime.sort(key = lambda x : x[2])
  print(Eprime)
  F = set()
  sets = list(set())
  for v in V_U:
    sets.append({v})
  print(sets)
  for u,v,l in Eprime:
    findu = find_set(u,sets)
    findv = find_set(v,sets)
    if findu != findv:
      F.add((u,v,l))
      merge_set(u,v,sets)
  spanning = is_spanning(V_U, F)
  print(str.format("Is Spanning: {}", spanning))
  if not spanning:
    pass
    #exit()
  # Create edge set Ebar
  Ebar = list()
  for u in V:
    if u in U:
      print(u)
      print(E[u])
    for v,l in E[u]:
      if u in U and v not in U:
        Ebar.append((u,v,l))
      if v in U and u not in U:
        Ebar.append((v,u,l))
  print("Ebar = ",Ebar)
  
  # Apply Kruskal's algorithm to Ebar
  # Sort ebar by weight
  Ebar.sort(key = lambda x : x[2])
  print(Ebar)
  # makeset(u) for u in U
  for u in U:
    sets.append({u})
  print(sets)
  # FindSet u,v in Ebar
  for u,v,l in Ebar:
    findu = find_set(u,sets)
    findv = find_set(v,sets)
    print("u = ",u)
    if findu != findv and not (u in U and v in U):
      F.add((u,v,l))
      merge_set(u,v,sets)
  spanning = is_spanning(U, F)
  print(str.format("Is Spanning: {}", spanning))
  if not spanning:
    pass
    #exit()
  print("Final Tree = ", F)