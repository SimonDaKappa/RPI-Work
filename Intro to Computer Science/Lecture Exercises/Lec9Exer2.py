census = [ 340, 589, 959, 1372, 1918, 2428, 3097, 3880, 4382, 5082, 5997, 7268, 9113, 10385, 12588, 13479, 14830, 16782, 8236, 17558, 17990, 18976, 19378 ]
def decades(inputlist): #adds up %change by decade and then averages.
    s = 0
    for x in range(len(inputlist)-1):
         s += (inputlist[x+1]-inputlist[x])/inputlist[x]*100
    return s/(len(inputlist)-1)

print("Average = {:.1f}".format(decades(census)),"%",sep='')