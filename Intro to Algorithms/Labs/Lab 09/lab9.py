import sys

def matrixDP(dims, i, j):
  if i == j:
    return 0

  # If subdimsroblem not solved already
  if dp[i][j] == -1:
    dp[i][j] = sys.maxsize
    for k in range(i,j):
      dp[i][j] = min(dp[i][j], matrixDP(dims, i, k) + matrixDP(dims, k + 1, j) + dims[i-1] * dims[k] * dims[j])

  return dp[i][j]  

if __name__ == "__main__":
  #dims = [10, 20, 30] # Answer is 60000
  #dims = [1, 2, 3, 4] # Answer is 18
  dims = [10,20,30,40,50,40,10,50,20]
  n = len(dims)
  # nxn memoization matrix
  dp = [[-1 for i in range(n)] for j in range(n)]
  multCount = matrixDP(dims, 1, n-1)
  print("The minimum number of multiplications is", multCount)