# -*- coding: utf-8 -*-
import hw7_part1
import json
"""
Created on Wed Nov 18 12:07:36 2020

@author: Simon

dictionary  = dict()
for line in open("words_10percent.txt"):
    temp = line.split(",")
    dictionary[temp[0]] = []
    for i in range(1,len(temp)): #Universalizes the dictionary creation so that each line can have more than 2 values from split()
       dictionary[temp[0]].append(temp[i].strip())
print(dictionary)


d = dict()

d[0] = 10
print ( type(d.keys()))

print( 0 in d.keys() )

print( 1 in d.keys() )

"""
"    01234"
s = "simon"

si = s[:0] + s[1:] 
print(si)
i = 2
s2 =  s[:3] + s[4] + s[3] + s[5:]
print(s2)

s3 = s[:i] + 'X' + s[i+1:]
print(s3)

s4 = s[:5] + "X" + s[5:]
print(s4)

dic = {"s":{"sim":"on","gib":"son"},  "j":{"s":[1,23,4]}}
for letter in dic:
    print(dic[letter])

f1 = json.loads(open("movies.json").read())
"""
for movie in f1:
    try:
        if 'rating' not in f1.get(movie):
            print(movie)
    except:
        print(movie)
"""
f2 = json.loads(open("ratings.json").read())
try:
    print(type(f2["2427844"]))
except:
    print("does not exist")
    
print( f1['3618473']["rating"])