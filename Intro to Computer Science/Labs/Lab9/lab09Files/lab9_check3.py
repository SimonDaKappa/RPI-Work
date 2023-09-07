"""
Lab 9 - Check 3
"""

import lab9_check2

def main():
    birthdays = read_birthdays(input("Enter the name of a file ==> "))
    find_endpoints(birthdays)
    print(find_common_month(birthdays))

def read_birthdays(fname):
    birthdays = list()
    
    for line in open(fname):
        s = line.split()
        birthdays.append(Date(s[0],s[1],s[2]))
    return birthdays
    
def find_endpoints(birthdays):
    first = birthdays[0]
    last = birthdays[0]
    
    for date in birthdays:
        if date < first:
            first = date
        
        if date > last:
            last = date
    print(first,last)

def find_common_month(birthdays):
    months  = list(0 for x in range(13))
    for date in birthdays:
        months[int(date.month)] += 1
    return month_names[ months.index(max(months)) ]

if __name__ == "__main__":
    main()