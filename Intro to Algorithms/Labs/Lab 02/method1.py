# -*- coding: utf-8 -*-
"""
Created on Sat Jan 21 11:58:40 2023

@author: daovi
"""
import time
import sys
import random
import math

def method_1(num1, num2):
    num1_binary = bin(num1)[2:]
    num2_binary = bin(num2)[2:]

    result = 0
    #
    for digit in range(len(num2_binary)):
        #if the digit in the array is 1
        if num2_binary[digit] == "1":
            #adds num1 shifted to the left by the index in the num2_binary array
            result += num1 << digit
    #after the loop return the the final result 
    return result

if __name__ == "__main__":
    d = int(input("Enter d: "))
    
    total_time_1 = 0
    for i in range(10):
        num1 = random.randint(10**(d-1), 10**d-1)
        num2 = random.randint(10**(d-1), 10**d-1)
        
        start_time_1 = time.time()
        result_1 = method_1(num1, num2)
        end_time_1 = time.time()
        
        total_time_1 += end_time_1 - start_time_1
    
    average_time_1 = total_time_1/10
    print("The average time to multiply two {}-digit numbers using Method 1 is {:.5f} seconds".format(d, average_time_1))