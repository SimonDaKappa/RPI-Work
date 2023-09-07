def add(m,n):
    if n == 0:
        return m
    return add(m,n-1) + 1

def mult(m,n):
    if n == 0:
        return 0
    return  add( m, mult(m,n-1))

def power(m,n):
    if n==0:
        return 1
    return mult( m, pow(m,n-1))

if __name__ == "__main__":
    print(add(5,3))
    print(mult(5,3))
    print(mult(100,9))
    print(power(6,3))                                                                  
    #print(power(6,8)) #Exceeds maximum recursion depth very quickly, "+1" is computed m↑n times, add() is computer m^n times
