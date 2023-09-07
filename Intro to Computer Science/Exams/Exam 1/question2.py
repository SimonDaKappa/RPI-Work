#Questions2
def compare(p1,p2):
    score1 = p1.count("a")*p1.find("a") + p1.count("e")*p1.find("e") 
    score2 = p2.count("a")*p2.find("a") + p2.count("e")*p2.find("e") 
    score1-= (.1*2 + .2*(len(p1)-2) - .3)
    score2-= (.1*2 + .2*(len(p2)-2) - .3)
    if score1 > score2:
        print("Winner is player 1\n")
        print("Final scores are:")
        print("Player 1: Word= ",p1,",Score {:.2f}".format(score1),sep='')
        print("Player 2: Word= ",p2,",Score {:.2f}".format(score2),sep='')
    elif score2 > score1:
        print("Winner is player 2\n")
        ("Final scores are:")
        print("Player 1: Word= ",p1,",Score {:.2f}".format(score1),sep='')
        print("Player 2: Word= ",p2,",Score {:.2f}".format(score2),sep='')
    
    else:
        print("There is a tie between the two players\n")
        print("Final scores are:")
        print("Player 1: Word= ",p1,",Score {:.2f}".format(score1),sep='')
        print("Player 2: Word= ",p2,",Score {:.2f}".format(score2),sep='')
    
s1 = input("Player 1: Enter you word => ")
t2 = input("Player 2: Enter you word => ")    
compare(s1.lower(),t2.lower())