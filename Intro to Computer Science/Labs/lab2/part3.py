import math
print("Disk size in GB => ",end='')
base10size = int(input())
print(base10size)
base2size = math.floor((base10size*(10**9))/(2**30))
lostsize = abs(base2size - base10size)
print(base10size,'GB in base 10 is actually',base2size,'GB in base 2,',lostsize,'GB less than advertised.')
print("Input: ",base10size*'*')
print("Actual:",base2size*'*')