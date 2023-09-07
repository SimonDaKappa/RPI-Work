def find_min(listlist):
    if type(listlist[0][0]) == int or type(listlist[0][0]) == float:
        listmin = listlist[0][0]
        for _list in listlist:
            listmin = min(listmin,min(_list))
    elif type(listlist[0][0]) == str:
        listmin = listlist[0][0]
        for _list in listlist:
            for string in _list:
                if listmin > string:
                    listmin = string
    return listmin

if __name__ == "__main__":
    v = [ [ 11,12,3], [6, 8, 4], [ 17, 2, 18, 14] ]
    print("Min of list v: {} ".format(find_min(v)) )
    u = [ [ 'car', 'tailor', 'ball' ], ['dress'], ['can', 'cheese', 'ring' ], \
         [ 'rain', 'snow', 'sun' ] ]
    print("Min of list u: {} ".format(find_min(u)))