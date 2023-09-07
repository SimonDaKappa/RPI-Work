"""
Hw7 - Part 2
Simon Gibson
Note to grader: There are a lot of debug prints commented out, sorry
"""
import json

def main():
    """
    :description: Main code for program, gathers user inputs and calls movies_in_range and find_extremes, the two
    primary functions for this program
    :return: None
    :rtype: None
    

    """
    
    min_year = int(input("Min year => "))
    print(min_year)
    max_year = int(input("Max year => "))
    print(max_year)
    global w_imdb
    w_imdb = input("Weight for IMDB => ")
    print(w_imdb)
    w_imdb =float(w_imdb)
    
    global w_twitter
    w_twitter = input("Weight for Twitter => ")
    print(w_twitter)
    w_twitter = float(w_twitter)
    print()

    global imdb
    imdb = readfiles("movies.json")
    global twitter
    twitter = readfiles("ratings.json")
    global in_range
    in_range = movies_in_range(float(min_year),float(max_year))
    find_extremes(min_year,max_year)


def movies_in_range(min_year,max_year):
    """
    
    :param min_year: minimum year specified by user (inclusive)
    :type min_year: int
    :param max_year: maximum year specified by user (inclusive)
    :type max_year: int
    :return: Determines if a year from the given json file is "valid" (within year bounds and >= 3 Twitter reviews)
    creates mov_in_range, a set of all valid movies
    :rtype: set

    """
    global mov_in_range
    mov_in_range = set()
    for movie_key in imdb: #movie_key is the string of numbers that represents a movie in  movies.json
        if  (imdb[movie_key]["movie_year"] >= min_year and imdb[movie_key]["movie_year"] <= max_year ):
                #print( get_weighted_rating(movie_key))
                if get_weighted_rating(movie_key) != None:
                    mov_in_range.add( (get_weighted_rating(movie_key) ,tuple(imdb[movie_key]["genre"]), movie_key ) ) #index 0 of tuple is weighted score, 1 is genre, 2 is movie_key
    #print(mov_in_range) #dDebug
    return mov_in_range

def get_weighted_rating(movie): #I dont think ive ever had to use this many flags to debug what was once a single line of code jeez
    """
    :param movie: movie_key of a movie in user specified json file
    :type movie: string - Used as a key in json dictionaries
    :return: Returns the weighted output as a float if valid, as NoneType if not valid
    
    """
    try:
        #print() #formatting Debug
        #print() #Formatting Debug
        #print('type w_imdb',type(w_imdb)) #Debug
        imdb_rating = imdb[movie]["rating"]
        #print("type imdb_rating",type(imdb_rating)) #Debug
        #print(imdb_rating) #Debug
        #print(twitter[movie]) #Debug
        if len(twitter[movie]) < 3:
            return None
        twitter_rating = sum(twitter[movie])/len(twitter[movie])
        #print( twitter_rating) #Debug
        t1 = imdb_rating* w_imdb
        #print("imdb rate weighted", t1) #Debug
        t2 = twitter_rating * w_twitter
        #print("twitter rating weighted",t2) #Debug
        t3 = w_imdb + w_twitter
        #print("combined weight",t3) #Debug Flag
        
        out = (t1 + t2) / t3
        #print("output",out) #Debug once again 
        return out
        
    except: #Exception as e: # if only movie_key printed, then one of the two json files does not contain it, IDK what the float error is
        #if type(e) != KeyError:  #Debugging, keyerror only happens when movie_key printed
            #print(e) #Debugging
        pass
    
def find_extremes(min_year,max_year):
    """
    :return: None
    :rtype: None
    :description: Asks for genre from user constantly, outputs the valid movies in given genre of highest and lowest weighted rating
    """
    while(True):
        #Finding movies in range of given genre
        
        genre = input("What genre do you want to see? ")
        genre_in_range = list()
        print(genre)
        if genre.lower() == "stop":
            break
        print()
        for movie in mov_in_range:
            #print(movie[1]) #test
            for single_genre in movie[1]:
                if single_genre.lower() == genre.lower():
                    genre_in_range.append( (movie[0],movie[2]) )
        #print(genre_in_range)        
        genre_in_range = sorted(genre_in_range)
        
        if len(genre_in_range) == 0:
            print("No {} movie found in {} through {}".format(genre.title(),min_year,max_year)) #Case if no movies had genre
            print()
            continue
        #Using sorted genre_in_range to grab movie_keys of highest and lowest rated movie
        
        #print(genre_in_range)
        
        highest_key = genre_in_range[len(genre_in_range)-1][1]
        lowest_key = genre_in_range[0][1]

        #print(highest_key) #Debug
        #print(lowest_key)  #Debug

        print("Best:\n        Released in {}, {} has a rating of {:.2f}\n".format(imdb[highest_key]["movie_year"],imdb[highest_key]["name"],genre_in_range[-1][0]))
        print("Worst:\n        Released in {}, {} has a rating of {:.2f}\n".format(imdb[lowest_key]["movie_year"],imdb[lowest_key]["name"],genre_in_range[0][0]))    
        
def readfiles(fname):
    return json.loads(open(fname).read())

if __name__ == "__main__":
    main()