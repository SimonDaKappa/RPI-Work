import hw4_util

def start():
    while(True):
        week = int(input("...\r\nPlease enter the index for a week: "))
        print(week)
        if week > 0 and week <= 29:
           global data 
           data = get_Data(week)
           if data:
                requests()
        elif( week > 29):
            print("No data for that week")
        else:
            break

def get_Data(week): # 1= most recent, 2 = second most recent, etc.
    return hw4_util.part2_get_week(week)

def requests():
    """Asks the user for the datapoint they want and then calculates and prints it"""
    request = input("Request (daily, pct, quar, high): ")
    print(request)
    
    if request.lower() == "daily":
        state= input("Enter the state: ")
        print(state)
        try:
            state_index = [ x[0] for x in data].index(state)
            print("Average daily positives per 100K population: {:.1f}".format(avg_daily(state_index)))
        except:
            print("State",state,"not found")
    
    elif request.lower() == "pct":
        state= input("Enter the state: ")
        print(state)
        try:
            state_index = [ x[0] for x in data].index(state)
            print("Average daily positive percent: {:.1f}".format(percent_daily(state_index)))
        except:
            print("State",state,"not found")
    
    elif request.lower() == "quar":
        print("Quarantine states:")
        weekly_quarantined()

    elif request.lower() == "high":
        print("State with highest infection rate is",highest_infr()[1])
        print("Rate is {:.1f}".format( highest_infr()[0] ),"per 100,000 people"  )
    
    else:
        print("Unrecognized request")


def percent_daily(state_index,d1 = 0, d2 = 0):
    """Calculates the average daily percentage of positive cases for the past week of a given state"""
    for x in range(2,9):
        d1 += data[state_index][x] 
        d2 += (data[state_index][x+7] + data[state_index][x])
    return d1/d2 * 100

def avg_daily(state_index,s = 0):
    """Calculates the average number of cases per 100,000 people daily"""
    for x in range(2,9):
        s += data[state_index][x]
    s/= 7
    return (s / data[state_index][1]) * 100000


def weekly_quarantined(quarantined = []):
    """Creates and prints a list of all the states in a given week that have daily percents > 10% or cases / 100,000 > 10"""
    #print(data) Testing 
    for state_index in range(len(data)):
        #hw4_util.print_abbreviations(quarantined) Testing
        if avg_daily(state_index) > 10 or percent_daily(state_index) > 10:
            quarantined.append(data[state_index][0])
    
    hw4_util.print_abbreviations(quarantined)

def highest_infr(highest = 0, temp = 0, s = 0):
    """Compares the avg daily cases per 100,000 of each state and finds the max"""
    for state_index in range(len(data)):
        highest = max(highest, avg_daily(state_index)) 
        if highest > temp:
            s = state_index
        temp = highest
    return (highest,data[s][0])







start()