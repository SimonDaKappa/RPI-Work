def add_time(tuple1,tuple2):
    mins  = tuple1[2] + tuple2[2]
    hours = int(mins/60) + tuple1[1] + tuple2[1]
    mins = int((mins%60))
    days = int(hours/24) + tuple1[0] + tuple2[0]
    hours = int((hours%24))
    return days,hours,mins
    
def sub_time(tuple1,tuple2):
    days = tuple1[0]- tuple2[0]
    hours = tuple1[1] - tuple2[1]
    if hours < 0:
        hours += 24
        days -= 1
    mins = tuple1[2] - tuple2[2]
    if mins < 0:
        mins += 60
        hours -= 1
        if hours < 0:
            hours += 24
            days -= 1
    return days,hours,mins

tuple1 = (int(input("Enter days for time 1=> ")),int(input("Enter hours or time 1=> ")),int(input("Enter for mins time 1=> ")))
tuple2 = (int(input("Enter days for time 2=> ")),int(input("Enter for hours time 2=> ")),int(input("Enter for mins time 2=> ")))
choice = input("Enter +/- =>")
if choice != "-" and choice != "+":
    print("Illegal operation",choice)

elif choice == "-":
    result = sub_time(tuple1,tuple2)
    print("Answer => ",tuple1[0],":",tuple1[1],":",tuple1[2]," ",choice," ",tuple2[1],":",tuple2[1],":",tuple2[2]," = ",result[0],":",result[1],":",result[2],sep="")
else:
    result  = add_time(tuple1,tuple2)
    print("Answer => ",tuple1[0],":",tuple1[1],":",tuple1[2]," ",choice," ",tuple2[1],":",tuple2[1],":",tuple2[2]," = ",result[0],":",result[1],":",result[2],sep="")