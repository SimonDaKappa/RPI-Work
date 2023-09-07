import lab04_util
restaurants = lab04_util.read_yelp("yelp.txt")
print(restaurants[0])

def print_info(restaurants,i): 
    address = restaurants[i][3].split('+')
    output = ""
    for x in range(len(address)):
        output+= "\n\t\t" + address[x]
    average = sum(restaurants[i][6])/len(restaurants[i][6])
    return restaurants[i][0]+output + "\nAverage Score: {:.2f}".format(average) +'\n'

    
    
print(print_info(restaurants,0))
print(print_info(restaurants,4))
print(print_info(restaurants,42))