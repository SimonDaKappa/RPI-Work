#19th versions of word type count aaaaaaaaaaaaa
import string
happy = ["laugh","happiness","love","excellent","good","smile"]
sad = ["bad","sad","terrible","horrible","problem","hate"]
#python is foreach by defualt? wack.
def number_happy(wordlist):
    c = 0
    for i in range(len(wordlist)):
        for j in range(len(happy)):
            if wordlist[i].find(happy[j]) != -1:
                c+=1
    return c

def number_sad(wordlist):
    c = 0
    for i in range(len(wordlist)):
        for j in range(len(sad)):
            if wordlist[i].find(sad[j]) != -1:
                c+=1
    return c

def tone(sentence):
    sentence  = strip_punctuation(sentence).lower().split()
    
    h = number_happy(sentence)
    s = number_sad(sentence)
    if h == s:
        return "Sentiment: " + "+"*h + "-"*s + "\nThis is a neutral sentence."
    if h > s:
        return "Sentiment: " + "+"*h + "-"*s + "\nThis is a happy sentence."
    return "Sentiment: " + "+"*h + "-"*s + "\nThis is a sad sentence."

def strip_punctuation(sentence): #sentence = sentence.translate(str.maketrans(' ',' ',  string.punctuation)) tried this method, doesnt work, not smart enough to know why. Stackoverflow guy said its about 10x efficient as a loop like mine
    temp = sentence
    for x in temp:
        if x in string.punctuation:
            temp = temp.replace(x, " ")
    return temp

sentence = input("Enter a sentence => ")
print(sentence,tone(sentence),sep='\n')
