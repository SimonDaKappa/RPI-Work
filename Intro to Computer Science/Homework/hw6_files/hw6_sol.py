# -*- coding: utf-8 -*-
"""
Created on Wed Nov  4 19:15:52 2020

@author: Simon
"""

def main():
    """Main function for program, calls all other functions and does basic assignments"""
    files = get_files()
    f1 = open(files[0])
    f2 = open(files[1])
    stop = open_stopwords(open(files[2]))
    
    maxsep = int(input("Enter the maximum separation between words in a pair ==> "))
    print(maxsep,"\n")
    
    f1_parsed = remove_stopwords(parse(f1),stop,1)
    f2_parsed = remove_stopwords(parse(f2),stop,2)
    
    f1_eval = eval(f1_parsed,files[0],maxsep)
    f2_eval = eval(f2_parsed,files[1],maxsep)
    
   # print(f1_eval[2])
   # print(f2_eval[2])
    
    compare_files(f1_eval,f2_eval,files[0],files[1])
    
    
    
    
def compare_files(f1_eval,f2_eval,f1,f2):
    """
    Things to compare:
        1. Which file has average longer word length (Rough measure of complexity)
        2. Jaccard similarity len(A & B)/len(A | B) :
            a) Calculate for overall word use in documents
            b) Calculate for each word in set of word length (the setify_words() for each document eval[2])
            c) Calculate between word pair set (eval[4])
    """
    print("Summary comparison")
    #1
    if f1_eval[0] > f2_eval[0]:
        print("1. {} on average uses longer words than {}".format(f1,f2))
    else:
        print("1. {} on average uses longer words than {}".format(f2,f1))

    #2 Jaccard similarity
    print("2. Overall word use similarity: {:.3f}".format(get_jaccard_similarity(set(f1_eval[5]), set(f2_eval[5]))))
    print("3. Word use similarity by length:")
    
    
    for i in range(max(len(f1_eval[2]),len(f2_eval[2]))):
        print("{:>4}:".format(i + 1),end='')
        if i > len(f1_eval[2]) or i > len(f2_eval[2]):
            print(" 0.0000")
        else:
            try:
                print(" {:.4f}".format(get_jaccard_similarity(f1_eval[2][i], f2_eval[2][i])))
            except: #usually flagged by a divide by 0 error
                print(" 0.0000")
    
    print("4. Word pair similarity: {:.4f}".format( get_jaccard_similarity(set(f1_eval[3]) ,set(f2_eval[3]) ) )  )
    
    
    
    
def get_jaccard_similarity(set1,set2): #Note: Only works with sets, not lists or othe iterables
    return len(set1 & set2)/len(set1 | set2)




def eval(words,fname,maxsep):
    """ Calls all the functions for single parsed file analysis
        Returns:                                   0                   1             2           3                4                      5               
            Tuple of length six in order (average word length, unique word ratio, Word sets, Word pairs, Unique pair ratio, original parsed file list)
    """  
    print("Evaluating document",fname)
    avg = avg_word_length(words)
    print("1. Average word length: {:.2f}".format(avg))
    u_w_r = unique_word_ratio(words)
    print("2. Ratio of distinct words to total words: {:.3f}".format(u_w_r))
    print("3. Word sets for document ",fname,":",sep = '')   
    s_w = setify_words(words)
    print("4. Word pairs for document",fname)
    pairs= word_pairs(words,maxsep)
    u_p_r = unique_pair_ratio(pairs)
    print("5. Ratio of distinct word pairs to total: {:.3f}".format(u_p_r))
    print()
    return (avg,u_w_r,s_w,pairs,u_p_r,words)
    



def avg_word_length(words):
    """ Finds and returns average word length of single parsed file"""
    c = 0
    for word in words:
        c += len(word)
    return c/len(words)
    



def unique_word_ratio(words):
    '''Finds and returns ratio of unique words to total words of single parsed file'''
    return len(set(words)) / len(words)




def setify_words(words): #I love this function name :)     
    """ 
    Finds the longest word in a list, creates the len(longest word) amount of sets, sorts words into their set that represents their length
    """
    biggest_len = 0
    length_list = []
    for word in words: #finding the max word length
        biggest_len = max(biggest_len, len(word))

    for i in range(biggest_len): #creates biggest_len sets
        length_list.append(set())
        
    for word in words: #adds word to set which represents the words length
        length_list[len(word) - 1].add(word)
        
    for length in enumerate(length_list): #length[0] = iterator length[1] = set representing iterator +1 length
        print("{:>4}".format(length[0] + 1),":{:>4}".format(len(length[1])),":", sep='',end='')
        print_set(sorted(length[1]))
    return length_list




def print_set(lengths):
    """ Helper function for settify_words() that formats the printing of the final output"""
    if len(lengths) <=6:
        for x in lengths:
            print('',x,end='')
        print()
    else:
        print("",lengths[0],lengths[1],lengths[2],"...",lengths[-3],lengths[-2],lengths[-1])




def word_pairs(words,n): #n is the max seperation
    """
    Note: Do not have to check if there are more than 5 pairs generated, I can assume there are.
    Part 1: Generating all pairs with n seperation
    """
    pairs = []
    for i in range(len(words)-1):
        c = 1
        while (c <= n):
            try:
                pairs.append( (words[i],words[i+c]) )
            except:
                """This should only fail when at i > len(words) - n. disregard the error, and let the loop only succesfully append pairs that arent out of range"""
                pass
            c+= 1
    #print(pairs) Testing
    """
    Part 2: Sorting by alphebatizing, and printing the first and last 5 pairs after sort
    """
    sorted_pairs = []
    strings = []
    for pair in pairs: #convert each pair to a string, add to a list of strings, sort that list and then put back into tuple 
        if pair[0] > pair[1]:  # Basically just formatting the string so sorting alphabetically always has the smallest string in the front of each tuple  
            strings.append(str(pair[1]) + " " + str(pair[0]) )
        else:
            strings.append(str(pair[0]) + " " + str(pair[1]) )
    strings = sorted(strings)
    
    for string in strings: #recombining into tuples
        sorted_pairs.append(tuple(string.split()))
    
    
    print(" ",len(set(sorted_pairs)),"distinct pairs")
    
    for i in range(5): #Prints the first 5 sorted pairs
        print("  {} {}".format(sorted_pairs[i][0],sorted_pairs[i][1])) 
    print("  ...")
    for i in range(len(sorted_pairs)-5,len(sorted_pairs)): #Prints the last 5 sorted pairs
        print("  {} {}".format(sorted_pairs[i][0],sorted_pairs[i][1]))

    return sorted_pairs




def remove_duplicates_ordered(seq): #removes duplicate pairs while preserving the order, while set would not
    seen = set()
    seen_add = seen.add
    return [x for x in seq if not (x in seen or seen_add(x))]




def unique_pair_ratio(pairs): #passed in already sorted pairs, with each pair sorted itself, hopefully
    return len(set(pairs))/len(pairs)
   
    
   
    
def open_stopwords(stop):
    """ Formats all the words in stop.txt into a set of words with non letters removed """
    stopwords = []
    for line in stop:
        line = line.split()
        
        for word in line:
            word = word.strip()
            tempstr = ""
            
            for char in range(len(word)): 
                if word[char].isalpha():
                    tempstr += word[char]
        
        stopwords.append(tempstr)
    return set(stopwords)




def parse(file1):
    """Converts file to list of strings: Removes non alphabet characters, strips whitespace"""
    strings = []
    
    for line in file1: #Turns the file into a list of non-whitespace strings
        temp = line.split()
        for string in temp:
            strings.append(string.strip())
    
    for i in range(len(strings)):
        strings[i] = strings[i].lower()
        tempstring = ""
        for c in range(len ( strings[i] )):
            if strings[i][c].isalpha():
                tempstring+= strings[i][c]
        strings[i] = tempstring
    new = strings.copy()
    
    c = 0
    for i in range(len(strings)):
        if strings[i] == "":
            del new[i - c]
            c+=1
    
    return new
      


          
def remove_stopwords(strings,stop,filenum):
    """ Checks if a word in passed list of words is in the set stopwords, if so it removes it from a copy of passed list, returns copy"""
    new = strings.copy()
    c = 0
    for i in range(len(strings)):
        x = i - c
        if strings[i] in stop:
            del new[x]
            c+=1
    return new
            



def get_files():
    f1 = input("Enter the first file to analyze and compare ==> ")
    print(f1)
    f2 = input("Enter the second file to analyze and compare ==> ")
    print(f2)
    f3 = "stop.txt"
    return (f1,f2,f3)




if __name__ == "__main__":
    main()