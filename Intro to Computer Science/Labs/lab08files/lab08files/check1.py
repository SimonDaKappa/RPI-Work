"""
Simon Gibson
Lab 08 - Checkpoint 1
"""

def main():
    file  = open(input('Enter a file namee ==> '))
        

def get_words(description):
    words  = description.split()
    word_set = set()

    for i in range(len(words)):
        words[i] = words[i].replace('.'," ")
        words[i] = words[i].replace(','," ")
        words[i] = words[i].replace('('," ")
        words[i] = words[i].replace(')'," ")
        words[i] = words[i].replace('"'," ").strip()
        if words[i].isalpha() and len(words[i]) >= 4:
            word_set.add(words[i].lower())

    
    return word_set

if __name__ == "__main__":
    fname = "wrpi.txt"
    file = open(fname)
    clubs = []
    for line in file:
        clubs.append(line.split("|"))
    print(fname)
    print(get_words(clubs[0][1]))
    print(len(get_words(clubs[0][1])))
    