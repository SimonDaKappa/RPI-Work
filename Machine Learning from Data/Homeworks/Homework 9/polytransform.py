def polyTransform(X, deg = 8, doLegendre = True):
  offset = 1 if len(X[0]) == 3 else 0
  transformed = []
  for i in range(len(X)):
    transformed.append([])
    if doLegendre:
      Lx1 = recLegPoly(deg, X[i][0+offset])
      Lx2 = recLegPoly(deg, X[i][1+offset])
    for j in range(deg+1):
      for k in range(deg+1):
        if j+k <= deg:
          if doLegendre:
            transformed[i].append(Lx1[j]*Lx2[k])
          else:
            transformed[i].append(X[i][0+offset]**j * X[i][1+offset]**k)
  return np.array(transformed)