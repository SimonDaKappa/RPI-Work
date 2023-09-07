def hashtag(string):
    return "#" + string.title().replace(" ",'')
phrase = 'Things you wish you knew as a freshman'
print('The phrase "',phrase,'"\nbecomes the hashtag "',hashtag(phrase),'"',sep='')
        
