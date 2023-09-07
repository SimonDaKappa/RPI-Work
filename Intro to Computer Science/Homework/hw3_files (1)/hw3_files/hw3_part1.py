import syllables

def calculate(paragraph):
    """The main body of the program, which creates the lists of words and sentences in the paragraph, calls all other functions, and then prints their outputs"""
    hardwords = []
    words = []
    sentence_split = paragraph.split(".")
    for x in range(len(sentence_split)):
        temp = sentence_split[x].split()
        words.append(temp)
    ASL = get_ASL(words)
    ASYL = get_ASYL(words)
    PHW = hard_word_percent(words,hardwords)
    GFRI = 0.4*(ASL + PHW)
    FKRI = 206.835-1.015*ASL-86.4*ASYL
    print("\nHere are the hard words in this paragraph:\r")
    print(hardwords,end="\r\n")
    print("Statistics: ASL:{:.2f}".format(ASL)," PHW:{:.2f}".format(PHW),"% ASYL:{:.2f}".format(ASYL),sep='',end='\r\n')
    print("Readability index (GFRI): {:.2f}".format(GFRI),end='\r\n')
    print("Readability index (FKRI): {:.2f}".format(FKRI),end='\r\n')
   
    
   
    
def get_ASL(words):
    """Counts the total number of words and then divides it by the number of sentences"""
    word_count = 0
    for sentence in words:
        word_count +=len(sentence)
    return word_count/(len(words)-1)

def get_ASYL(words):
    """DEtermines the total number of syllables in the paragraph and then divides it by the number of words
    \ in the paragraph"""
    syll = 0 
    length = 0
    for sentence in words:
        for word in sentence:
            syll += syllables.find_num_syllables(word)
            length+=1
    return syll/length

def hard_word_percent(words,hardwords):
    """Calls is_word_hard to determine number of hard words in paragraph and the finds the percent of words that are
    \ hard"""
    c = word_count = 0
    for sentence in words:
       for word in sentence: 
           if(is_word_hard(word)):
               if word not in hardwords:
                   hardwords.append(word)
               c+=1
           word_count+=1    
    return c/word_count*100

def is_word_hard(word): 
    """Determines is passed word is hard"""
    num = syllables.find_num_syllables(word)
    if num >= 3 and not ("-" in word):
        return True
    elif(num == 3 and not(word.endswith("ed") or word.endswith('es'))):
        return True
    return False


paragraph = input("Enter a paragraph => ")
print(paragraph,end='')
calculate(paragraph)