'''
Simon Gibson - Check 1
'''


class Date(object):
    def __init__(self,y=1900,m=1,d=1):
        self.year = y
        self.month = m
        self.day = d
        
    def __str__(self):
        out = str(self.year).rjust(4,'0') + "/" + str(self.month).rjust(2,'0') + "/" + str(self.day).rjust(2,'0')
        return out

    def same_day_in_year(self,Date): 
        if self.month == Date.month and self.day == Date.day:
            return True
        return False

if __name__ == "__main__":
    d1 = Date(1972, 3, 27)
    d2 = Date(1998, 4, 13)
    d3 = Date(1996, 4, 13)
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    print("d1.same_day_in_year(d2)", d1.same_day_in_year(d2))
    print("d2.same_day_in_year(d3)", d2.same_day_in_year(d3)) 
    print()


