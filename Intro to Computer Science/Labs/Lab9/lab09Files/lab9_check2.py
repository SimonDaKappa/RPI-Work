"""
Lab 9 - Check 2
"""

days_in_month = [ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]
month_names = [ '', 'January', 'February', 'March', 'April', 'May', 'June', 'July',\
                    'August','September', 'October', 'November', 'December' ]
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
    
    def is_leap_year(self):
        if self.year % 4 != 0 or (self.year % 100 == 0 and self.year % 400 != 0):
            return False
        return True
    
    def __lt__(self,Date):
        if Date.year > self.year:
            return True
        elif Date.year == self.year:
            if Date.month > self.month:
                return True
            elif Date.month == self.month:
                if Date.day > self.day:
                    return True
                return False
        return False



if __name__ == "__main__":
    d1 = Date(1972, 3, 27)
    d2 = Date(1998, 3, 12)
    d3 = Date(1998, 4, 13)
    print("d1: " + str(d1))
    print("d2: " + str(d2))
    print("d3: " + str(d3))
    print("d1.same_day_in_year(d2)", d1.same_day_in_year(d2))
    print("d2.same_day_in_year(d3)", d2.same_day_in_year(d3)) 
    print()
    print(d1 < d2)
    print(d2 < d3)
    print()
    d4 = Date(2000,8,13)
    d5 = Date(2400,9,13)
    d6 = Date(2100,12,3)
    d7 = Date(1293,5,29)
    print(d1.is_leap_year())
    print(d4.is_leap_year())
    print(d5.is_leap_year())
    print(d6.is_leap_year())
    print(d7.is_leap_year())
        