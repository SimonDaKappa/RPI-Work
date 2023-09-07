#Finds change for item based on amount payed

Item=('Wafer','Soda', 'Chocolate','Breakfast Bar','Biscuits','Peanuts')
Price=(2.06,1.55,4.15,3.12,3.47,5.99)


print("Available Options:", Item)
choice = int(input("Enter the item number from the list shown above =>"))
print(choice)
choice-=1
print("Payment due :$",Price[choice], sep='')

def payment():
    one = int(input("Enter One Dollar bills =>"))
    quarter = int(input("Enter Quarters =>"))
    dime = int(input("Enter Dimes =>"))
    nickel = int(input("Enter Nickels =>"))
    penny = int(input("Enter pennies =>"))
    return one + .25*quarter + .1*dime +.05*nickel + .01*penny

change = round(payment() - Price[choice],2)

if change <0:
    change = -change
    print("You need to pay",change,"dollars more") 
elif change == 0:
    print("Thank you! Your Transaction is complete")
else:
    print("Your change due is"-change,"dollars")
    one_due = int(change / 1)
    change -= round(one_due,2)
    quart_due = int(change / .25)
    change -=  round(quart_due * .25,2)
    change  = float("{:.2f}".format(change)) #SUCH A FUCKING PAINFUL WORKAROUND WHY DOES PYTHON CANT .1 BE .1 and not .09999999999999999 WASTE OF TIME BRUH
    dime_due = int(change / .1 )
    change -= round(dime_due*.1,2)
    nickel_due = int(change / .05)
    change -= round(nickel_due *.05,2)
    penny_due = int(change / .01)
    change -= round(penny_due,2)
    print("Please collect the following:")
    print("Collect",one_due,"one dollar bills")
    print("Collect",quart_due,"quarters")
    print("Collect",dime_due,"dimes")
    print("Collect",nickel_due,"nickels")
    print("Collect",penny_due,"pennies")
