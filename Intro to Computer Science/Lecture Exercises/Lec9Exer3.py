val = []
c = 0
while True: #appends the inputted value onto val[] if != 0, else it breaks the loop.
    x = int(input("Enter a value (0 to end): "))
    print(x)
    if x != 0:
        c+=1
        val.append(x)
    else:
        break
print("Min:",min(val))
print("Max:",max(val))
print("Avg: {:.1f}".format(sum(val)/c))