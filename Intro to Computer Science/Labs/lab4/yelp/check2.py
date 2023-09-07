import lab04_util

def print_info(restaurants,i): 
    address = restaurants[i][3].split('+')
    output = ""
    for x in range(len(address)):
        output+= "\n\t\t" + address[x] 
    average = test_print(restaurants,i)
    return restaurants[i][0]+output + "\n" + average +'\n'


def test_print(restaurants,i):
    if len(restaurants[i][6]) > 3:
        length = len(restaurants[i][6]) - 2
        average = (sum(restaurants[i][6]) - max(restaurants[i][6]) - min(restaurants[i][6])) /length
    else:
        length = len(restaurants[i][6])
        average = sum(restaurants[i][6])/len(restaurants[i][6])
    if(average >= 4):
        return "This restaurant is rated very good, based on " + str(length) + " reviews."
    elif average >=3:
        return "This restaurant is rated above average, based on " + str(length) + " reviews."
    elif average >=2:
        return "This restaurant is rated average, based on " + str(length) + " reviews."
    return"This restaurant is rated bad, based on " + str(length) + " reviews."
    
restaurants = lab04_util.read_yelp("yelp.txt")
while(True):
    chosen_rest = int(input("Enter a restaurant from 1 to len(restaurants): ")) -1 
    if chosen_rest in range(len(restaurants)) and chosen_rest>=0:
        print(print_info(restaurants,chosen_rest))
    else:
        print("Input out of range!")
        break
