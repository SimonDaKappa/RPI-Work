class Environment: #This should follow the require outline? Uses functions and recycles variables. I just wanted to mess around with classes before we are required to learn them. 
    def __init__(self, bpop, fpop, years):
        self.bpop = bpop
        self.fpop = fpop
        self.years = years

    def getpopulations(self): #Calculates and returns the populations for the next year in a tuple
            self.bpop_next = max(0, int((10*self.bpop)/(1+0.1*self.bpop) - 0.05*self.bpop*self.fpop))
            self.fpop_next = max(0, int((0.4 * self.fpop + 0.02 * self.fpop * self.bpop)))
            return self.bpop_next,self.fpop_next
        
    def calculate(self): #Loops over based over the amount of years given and prints the populations of each year.
        c = 1
        print("Year",c,self.bpop,self.fpop)
        while c<=self.years:
            c+=1
            temp = self.getpopulations()
            print("Year",c,temp[0],temp[1])
            self.bpop = temp[0]
            self.fpop = temp[1]

bpop = int(input("Number of bunnies ==> "))
print(bpop)
fpop = int(input("Number of foxes ==> "))
print(fpop)
test = Environment(bpop,fpop,4)
test.calculate()

