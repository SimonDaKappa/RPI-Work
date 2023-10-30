

def canJump(nums):
  idx = len(nums)-1
  i=idx
  for i in range(len(nums)-1,-1,-1):
    if i < idx and idx - i <= nums[i]:
      print(str.format("i:{}, idx:{}",i,idx))
      idx = i
  print(str.format("Finished! i:{}, idx:{}",i,idx))
  return idx == 0

if __name__ == '__main__':
  print(canJump([2,3,1,1,4]))