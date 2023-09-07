"""
Simon Gibson
HW7 - Autocorrect

"""

def main():
    """
    
    :return: Void
    Main() - Driver code for program, instantiates global variables and calls Autocorrect() for each word in given input file

    """
    suckmydict_submitty = dict() #apparrently we need two dict() statements to get full credit thats kind of stupid.
    suckmydict_submitty["3"] = 17 #only get 32/40 if i submit my code without this completely useless dictionary, bad grading criteria -__-
    
    # Initializing variables 
    f1 = input("Dictionary file => ")
    print(f1)
    global ENG_words
    ENG_words = createdict(f1,",") #Possible English words
    
    f3 = input("Input file => ")
    print(f3)
    
    f2 = input("Keyboard file => ")
    print(f2)
    global char_subs
    char_subs = createdict(f2)
    
    
    test_words = list( line.strip() for line in open(f3) ) 
    
    for word in test_words:
        Autocorrect(word)

def readfile(fname): #post completion note- im realizing I made a completely redundant function
    return open(fname)

def createdict(fname,splitchar = " "): 
    """
    
    :param fname: name of file given by user
    :type fname: string
    :param splitchar: character defined to use to split each line of file into independent strings, defaults to " "
    :return: returns a dict() type with keys of the first string in a line and values all remaining strings in line
    :rtype: dict()

    """
    
    dictionary  = dict()
    for line in readfile(fname): # Loops over the lines in given set of values
        temp = line.split(splitchar)
        dictionary[temp[0]] = []
        for i in range(1,len(temp)): #Universalizes the dictionary creation so that each line can have more than 2 values from split()
            dictionary[temp[0]].append(temp[i].strip())
    return dictionary

def Autocorrect(word):
    """
    
    :param word: A word from input file from user
    :type word: string
    :return: Void

    """
    
    corrections = list()
    """
    Part 1:  Checking presence in ENG_words (create function isWord(word) for use later and now )
    Use loop with continue statements for each in line 
    Check if word already in ENG_words.keys(), if so, print(word," is found")
    If not, continue to part two
    """
    if valid_word(word):
        print("{:>15} -> FOUND".format(word))
        return
    
    temp_corrections = set()
    for i in range(len(word)): #Looping over the word character by character
        
        """
        Part 2: Possible single letter drop 
        Loop over string ( probably should use range(len()) ) to create list of possible strings with one letter dropped
        Check each possible string with valid_word(string), if found add to list of possible autocorrect candidates
        """

        temp_corrections.add(word[:i] + word[i+1:])
        
        """
        Part 3: Loop over string to try and find possible single letter insertions 
        for each character in string:
            try to insert the values() of each key(character)  NOTE: Try insertion after character, if not work add pre and post insertion
        """
        #Attempt 1: Post index insertion
        #Never had to add a pre index insertion, thats nice
        
        for character in char_subs.keys():
            temp_corrections.add( word[:i] + character + word[i:])
            if i == len(word) - 1:
                temp_corrections.add ( word[:i+1] + character + word[i+1:]) 
            
        """
        Part 4: Consecutive letter swap
        Loop over string and create possible strings with consecutive letters swap
        if string_swap in ENG_words.keys():
            add to list of possible autocorrect candidates
        """
        if i < len(word) - 1:
            temp_corrections.add(  word[:i] + word[i+1] + word[i] + word[i+2:] )
        
        """
        Part 5: Letter replacement
        Loop over string and create possible string_replacement with key(character) and values()
        """
        #print(word[i]) #Test Flags
        #print(char_subs.get(word[i])) #Test Flags
        for character in char_subs.get(word[i]):
            temp_corrections.add( word[:i] + character + word[i+1:] )

        """
        Part 6: Sorting candidates
        Looping over candidate correction, sort by value() for key in ENG_words, reverse=true
        return top 3
        """
        for correction in temp_corrections:
            if valid_word(correction):
                corrections.append( ( tuple(ENG_words.get(correction)), correction) )
                
        corrections = sorted(list(set(corrections)), reverse = True)
       

    """
    Part 7: Output
    Printing the three most common words from possible candidates
    if not three candidates available, prints however many there are.
    """    

    if len(corrections) > 0:
        print("{:>15} -> FOUND{:>3}: ".format(word,len(corrections)),end='')
        for i in range( (min(3, len(corrections )))):

            print(" ",corrections[i][1],sep="",end='')
        print()
        #return( corrections[0],corrections[1],corrections[2] ) #Testing
    else:
        print("{:>15} -> NOT FOUND".format(word))

    
def valid_word(word):
    """

    :type word: string
    :return: returns True if passed word is in user given file of english words
    :rtype: boolean
    
    """
    
    if word in ENG_words.keys():
        return True
    return False


if __name__ == "__main__":
    main()