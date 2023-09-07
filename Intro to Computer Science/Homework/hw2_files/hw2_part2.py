def encrypt(string):
    string = string.replace(" a","%4%")
    string = string.replace("he","7!")
    string = string.replace("e","9(*9(")
    string = string.replace("y","*%$")
    string = string.replace("u","@@@")
    string = string.replace("an","-?")
    string = string.replace("th","!@+3")
    string = string.replace("o","7654")
    string = string.replace("9","2")
    string = string.replace('ck','%4')
    return string

def decrypt(encrypted): #I%4%m%4%
    enc = encrypted.replace("%4","ck")  #Ick%mck%
    enc = enc.replace("2","9") #same 
    enc = enc.replace("7654","o") #same
    enc = enc.replace("!@+3","th") #same
    enc = enc.replace("-?","an") #same
    enc = enc.replace("@@@","u") #same       
    enc = enc.replace("*%$","y") #same
    enc = enc.replace("9(*9(","e") #same
    enc = enc.replace("7!","he") #same
    enc = enc.replace("%4%"," a") #same
    return enc

word = input("Enter a string to encode ==> ")
print(word)
e = encrypt(word)
d = decrypt(e)
print("\nEncrypted as ==>",e)
print("Difference in length ==> ",abs(len(word)-len(e)))
print("Deciphered as ==> " + d)
if word == d:
    print("Operation is reversible on the string.")
else:
    print("Operation is not reversible on the string.")
    