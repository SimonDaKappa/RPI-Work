values = [ 14, 10, 8, 19, 7, 13 ]
myshinsplintshurtreallybadrightnow = int(input("Enter a value: "))
print(myshinsplintshurtreallybadrightnow)
values.append(myshinsplintshurtreallybadrightnow)
Ithurtssobadicantconcentrate = int(input("Enter another value: "))
print(Ithurtssobadicantconcentrate)
values.insert(2,Ithurtssobadicantconcentrate)
print(values[3],values[-1])
print("Difference:",max(values)-min(values))
print("Average: {:.1f}".format(sum(values)/len(values))) 
values.sort()
median = 1/2*(values[int(float(len(values)/2)-1)]+values[int(float((len(values)/2)))])
print("Median: {:.1f}".format(median))

