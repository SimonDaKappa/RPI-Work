def frame_String(string):
    length = len(string)
    s1 = s3 = (length+6)*'*'
    s2 = '** ' + string + ' **'
    print(s1,'\n',s2,'\n',s3,"\n",sep='')
s1 ='Spanish Inquisition'
s2 = 'Ni'
frame_String(s1)
frame_String(s2)
