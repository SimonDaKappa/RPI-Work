"""bears berries and tourists:
    bears,tourists = populations
    berries = area of berry fields"""
import math

class environment():

    def __init__(self,bears,berries,years):
        self.years = years
        self.bears = bears
        self.berries = berries
        self.tourists = self.touristcount(self.bears,self.berries)
    
    def touristcount(self,bears,berries):
        temp = 0
        if(bears <4 or bears > 15):
            return 0
        else:
            for count in range(bears):
                if(count <= 10):
                    temp += 10000
                else: 
                    temp += 20000
            if(bears>10):
                temp+=10000
        return temp
    
    def find_next(self):
        self.bears_next = max(0,int(self.berries/(50*(self.bears+1)) + self.bears*0.60 - (math.log(1+self.tourists,10)*0.1)))
        self.berries_next = max(0,(self.berries*1.5) - (self.bears+1)*(self.berries/14) - (math.log(1+self.tourists,10)*0.05))
        self.tourists_next = max(0,int(self.touristcount(self.bears_next,self.berries_next)))
        return self.bears_next,self.berries_next,self.tourists_next
    
    def calculate(self):
        """This method finds calls find_next and recycles variables to print all of the populations in a given timeframe"""
        count = 1
        biggest = [self.bears,self.berries,self.tourists]
        smallest= [self.bears,self.berries,self.tourists]
        print("Year      Bears     Berry     Tourists  ")
        print("{:<10}{:<10}{:<10.1f}{:<10}".format(count,self.bears,self.berries,self.tourists))
        while count < self.years:
            count += 1
            temp = self.find_next()
            
            for x in range(len(biggest)): #Compares every index of smallest and biggest to current populations
                biggest[x] = max(biggest[x],temp[x])
                smallest[x] = min(temp[x],smallest[x])
            
            print("{:<10}{:<10}{:<10.1f}{:<10}".format(count,temp[0],temp[1],temp[2]))
            self.bears = temp[0]
            self.berries = temp[1]
            self.tourists = temp[2]            
        print("\r\n{:<10}{:<10}{:<10.1f}{:<10}".format("Min:",smallest[0],smallest[1],smallest[2]))
        print("{:<10}{:<10}{:<10.1f}{:<10}".format("Max:",biggest[0],biggest[1],biggest[2]))
    

bears = int(input("Number of bears => "))
print(bears)
berries = input("Size of berry area => ")
print(berries); berries = int(float(berries))

park = environment(bears,berries,10)
park.calculate()    