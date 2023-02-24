# -*- coding: utf-8 -*-
"""
Created on Sat Jan 21 11:55:10 2023

@author: daovi
"""
import time
import sys
import random
import math

def method_2(x, y):
    # if y is equal to 0, return 0
    if y == 0:
        return 0
    #call method_2 again with y being shifted to the right by 1 place
    z = method_2(x, math.floor(y >> 1))
    #if y is divisible by 2, returns z with the bits shifted to the left by 1 place
    if y % 2 == 0:
        return (z << 1)
    #else return x plus z with the bits shifted to the left by 1 place
    else:
        return x + (z << 1)
    
if __name__ == "__main__":
    d = int(input("Enter d: "))
    
    total_time_2 = 0
    for i in range(10):
        num1 = random.randint(10**(d-1), 10**d-1)
        num2 = random.randint(10**(d-1), 10**d-1)
        
        start_time_2 = time.time()
        result_2 = method_2(num1, num2)
        end_time_2 = time.time()
        
        total_time_2 += end_time_2 - start_time_2

    average_time_2 = total_time_2/10
    print("The average time to multiply two {}-digit numbers using Method 2 is {:.5f} seconds".format(d, average_time_2))