#cubic lattice packing density ~ .5236, error with submitty outputs at larger values, PAIN.
import math

def find_volume_sphere(radius):
    return 4/3*math.pi*radius**3

def find_volume_cube(side):
    return side**3

def boxmath(r,sales):
    desiredcount = math.ceil(sales*1.25)
    perside = int(math.ceil(desiredcount**(1/3)))
    total = perside**3
    sidesize  = r*perside*2.
    boxvolume = find_volume_cube(sidesize)
    excess = total - desiredcount
    wasteD = boxvolume - find_volume_sphere(r)*desiredcount
    wasteT = boxvolume - find_volume_sphere(r)*total
    print("\nThe machine needs to hold",perside,"gum balls along each edge.")
    print("Total edge length is {:.2f}".format(sidesize),"inches.")
    print("Target sales were ",desiredcount,", but the machine will hold ",excess," extra gum balls.",sep='')
    print("Wasted space is {:.2f}".format(wasteD),"cubic inches with the target number of gum balls,\nor {:.2f}".format(wasteT),"cubic inches if you fill up the machine.")

r = input("Enter the gum ball radius (in.) => ")
print(r)
r = float(r)
sales = input("Enter the weekly sales => ")
print(sales)
sales=int(sales)
boxmath(r,sales)

