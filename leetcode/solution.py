import numpy as np
import collections


class Solution:
    def kthFactor1(self, n: int, k: int) -> int:
        # Generate l
        factors_1, factors_2 = [], []
        for i in range(1, int(np.sqrt(n)) + 1):
            if n % i == 0:
                factors_1.append(i)
                factors_2.append(n//i)

        print(str.format("factors_1: {0}", factors_1))
        print(str.format("factors_2: {0}", factors_2))

        if factors_1[-1] == factors_2[-1]:
            factors_2.pop()

        if k <= len(factors_1):
            return factors_1[k-1]
        elif k <= len(factors_1) + len(factors_2):
            return factors_2[len(factors_2) - (k - len(factors_1))]
        else:
            return -1

    def kthFactor2(self, n: int, k: int) -> int:
        # Generate l
        factors_1 = []
        for i in range(1, int(np.sqrt(n)) + 1):
            if n % i == 0:
                if i*i != n:
                    factors_1.append(i)

        if k <= 2*len(factors_1):
            if k <= len(factors_1):
                return factors_1[k-1]
            else:
                return n//factors_1[len(factors_1) - (k - len(factors_1))]
        else:
            return -1

    def secondGreaterElement(self, nums: list[int]) -> list[int]:
      # Worst case O(n)
      ans = [-1] * len(nums)
      # Map of nums idx to its number of greater elements found if < 2
      notFoundYet = collections.defaultdict(int)
      for i in range(len(nums)):
        notFoundYet[i] = 0
        delIdx = []
        for idx, cnt in notFoundYet.items():
          
          print(str.format("i: {0}, idx: {1}", i, idx))
          if nums[i] > nums[idx]:
            notFoundYet[idx] += 1

          if notFoundYet[idx] == 2:
            ans[idx] = nums[i]
            delIdx.append(idx)
        
        for idx in delIdx:
          del notFoundYet[idx]
      return ans


if __name__ == "__main__":
    soln = Solution()
    print(soln.secondGreaterElement([1, 17, 18, 0, 18, 10, 20, 0]))
