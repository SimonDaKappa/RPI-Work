def recLegPoly(degree, x):
  # Returns L_{0}(x), L_{1}(x), ..., L_{degree}(x)
  L0, L1 = 1, x
  if degree < 0:
    raise ValueError("The order of Legendre polynomial can't be negative")
  
  if degree == 0:
    return [L0]
  elif degree == 1:
    return [L0, L1]

  Ls = [L0, L1]
  Lkm1, Lkm2 = L1, L0
  for k in range(2, degree+1):
    Lk = (2*k-1)*x*Lkm1/k - (k-1)*Lkm2/k
    Ls.append(Lk)
    Lkm2 = Lkm1
    Lkm1 = Lk
  return Ls