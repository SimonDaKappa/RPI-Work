import json


xy = 1
t = {"Simon":1,"James":1}
st = set( (x,t[x]) for x in t if t[x] == 1)
print(st)

