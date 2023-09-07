"""PART 1: Determining the strength of a password and returning a numerical value"""
import hw4_util

def how_hard(password):
    score = 0
    score += check_Length(password)[0]
    print(check_Length(password)[1])
     
    score += check_Case(password)[0]
    print(check_Case(password)[1])
     
    score += check_Digits(password)[0]
    print(check_Digits(password)[1])
     
    score += check_Punctuation(password)[0]
    print(check_Punctuation(password)[1])
     
    score += check_NY_License(password)[0]
    print(check_NY_License(password)[1])
     
    score += check_Common(password)[0]
    print(check_Common(password)[1])
    
    print("Combined Score:",score)
    
    if score >= 7:
        print("Password is excellent")
    elif score >= 5:
        print("Password is good")
    elif score >= 3:
        print("Password is fair")
    elif score >= 1:
        print("Password is poor")
    else:
        print("Password is rejected")
    
    
    
def check_Length(password):
    if len(password) == 6 or len(password) == 7:
        return (1,"Length: +1")
    elif len(password) >= 8 and len(password) <=10:
        return (2,"Length: +2")
    elif len(password) > 10:
        return (3,"Length: +3")
    else:
        return (0,"")

def check_Case(word): 
    countU = countL = 0
    for char in word:
        if char.isupper():
            countU+=1
        elif char.islower():
            countL+=1
    if countU >= 2 and countL >=2:
        return (2,"Cases: +2")
    elif countU >= 1 and countL >=1:
        return (1,"Cases: +1")
    return (0,"")

def check_Digits(word):
    countD = 0
    for char in word:
        if char.isdigit():
            countD+=1
    if countD >= 2:
        return (2,"Digits: +2")
    elif countD >= 1:
        return (1,"Digits: +1")
    return (0,"")

def check_Punctuation(word):
    countP = 0
    for char in word:
        if char == "!" or char == '@' or char == '#' or char == '$':
            countP+= 1
    if countP >= 2:
        return (2,"!@#$: +2")
    elif countP >= 1:
        return (1,"!@#$: +1")
    return (0,"")
        
def check_NY_License(word):
    if len(word) >= 6:
        for i in range(0,len(word)-6):
            if word[i].isupper() and word[i+1].isupper() and  word[i+2].isdigit() and  word[i+3].isdigit() and  word[i+4].isdigit() and  word[i+5].isdigit():
                return (-2,"License: -2")
    return (0,"")

def check_Common(word):
    common = hw4_util.part1_get_top()        
    for password in common:
        if password == word:
            return (-3,"Common: -3")
    return (0,"")


passw = input("Enter a password => ")
print(passw)
how_hard(passw)


