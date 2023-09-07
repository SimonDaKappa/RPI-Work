"""
Simon Gibson
Lab 8 - Checkpoint 3
"""

def main():
    """
    :whatitdo: main function, basic assignments and calls all other functions needed
    :return: None
    :rtype: None
    """
    fn1 = input("Enter the name of the first file ==> ")
    print(fn1)

    similar_clubs(fn1)    

def similar_clubs(fname1,fname2 = "allclubs.txt"):
    """
    :param fname1: file name given club
    :type fname1: string
    :param fname2: file name for all clubs
    :type fname2: string
    :return: None
    :rtype: print()
    """
    similarity_ranking = [] #Will only be properly ranked once sorted(reverse=True)
    given_club = process_file(fname1)
    all_clubs = process_file(fname2)
    
    for i in range(len(all_clubs)):
        #Check if name of club given is the one currently being accessed by for loop in all_clubs
        if all_clubs[i][0] != given_club[0][0]:
            similarity_ranking.append( [ len( given_club[0][1].intersection(all_clubs[i][1]) ), all_clubs[i][0]] )
    #Sorting by most common words
    similarity_ranking = sorted(similarity_ranking,reverse = True)
    
    for x in range(5):
        print(similarity_ranking[x])
        
def process_file(fname):
    """
    :param fname: file name
    :type fname: str
    :return: returns a list of sublists of length 2, indice 0 is the club name, indice 1 is a set: the description, formatted by get_words()
    """
    out = []
    for line in open(fname):
        temp = line.split("|")
        out.append([temp[0], get_words(temp[1])])
    return out
    
def get_words(description):
    """
    :type description: string
    :return: returns a set of all words greater than length 4 with punctuation removed
    """
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
    main()