class runner: #Wanted to try and learn how to do classes with arguments in python, first attempts so probably shouldve just instantiated new variables instead of the self. spam ¯\_(ツ)_/¯
    def __init__(self,name,t1,t2,t3,t4,t5):
        self.name = name
        self.t1 = t1
        self.t2 = t2
        self.t3 = t3
        self.t4 = t4
        self.t5 = t5

    def skew(self): #Returns the skew of a runners times of 5 miles 
        avg = (self.t1+self.t2+self.t3+self.t4+self.t5)/5
        var = (self.t1-avg)**2 + (self.t2-avg)**2 + (self.t3-avg)**2 + (self.t4-avg)**2 + (self.t5-avg)**2
        var /= 5
        skew = (self.t1-avg)**3 + (self.t2-avg)**3 + (self.t3-avg)**3 + (self.t4-avg)**3 + (self.t5-avg)**3
        skew /= 5
        skew = skew/var**3**0.5
    
        return self.name+"'s running times have a skew of {:.2f}".format(skew)

    def report_stats(self):
        temp = (self.t1,self.t2,self.t3,self.t4,self.t5)
        s = sum(temp)
        print(self.name,"'s stats-- min: ",min(temp)," max: ",max(temp)," avg: {:.1f}".format((s-min(temp)-max(temp))/3),sep='')
        

runner1 = runner("Stan",34,34,35,31,29)
print(runner1.skew())

runner2 = runner("Kyle",30,31,29,29,28)
print(runner2.skew())

runner3 = runner("Cartman",36,31,32,33,33)
print(runner3.skew())

runner4 = runner("Kenny",33,32,34,31,35)
print(runner4.skew())

runner5 = runner("Bebe",27,29,29,28,30)
print(runner5.skew())

runner1.report_stats()
runner2.report_stats()
runner3.report_stats()
runner4.report_stats()
runner5.report_stats()