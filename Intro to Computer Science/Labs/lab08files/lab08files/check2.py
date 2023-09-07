"""
Simon Gibson
Lab 08 - Checkpoint 2
Note: I have been trying to better my commenting and doc string-ing for the past few assignments, I think this is much easier to read than previous ones.
"""

def main():
    fn1 = input("Enter the name of the first file ==> ")
    print(fn1)
    fn2 = input("Enter the name of the second file ==> ")
    print(fn2)
    
    compare_files(fn1,fn2)
    
def compare_files(fname1,fname2):
    """
    :param fname1: file name
    :type fname1: string
    :param fname2: file name
    :type fname2: string
    :return: None
    """
    #Check the return type of process_file for info on indices
    f1 = process_file(fname1) 
    f2 = process_file(fname2)
    print("Comparing clubs {} and {}:".format(fname1,fname2))
    print("Same words:",f1[0][1].intersection(f2[0][1]),end= '\n\n') #Finds words common in both descriptions
    print("Unique to {}:".format(fname1),f1[0][1].difference(f2[0][1]),end= '\n\n') #Finds words unique to desc1
    print("Unique to {}:".format(fname2),f2[0][1].difference(f1[0][1])) #Finds words unique to desc2
    
def process_file(fname):
    """
    :param fname: file name
    :type fname: str
    :return: returns a list of length 2, indice 0 is the club name, indice 1 is a list: the description, formatted by get_words()
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
    #process_file("wrpi.txt")