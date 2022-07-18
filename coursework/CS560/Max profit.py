

import time

import matplotlib.pyplot as plt
#Ruben Rubalcaba
#CS 560
#Professor Hasan

def brute_force_find_max(A,low,high):
    max_left = low
    max_right = high
    profit = 0
    for i in range (low,high):
        max_profit = 0
        for j in range(low,high):
            max_profit = max_profit +A[i]
            if profit > max_profit:
                max_profit = profit
                max_left = i
                max_right = j
    return (max_left,max_right,max_profit)

def find_max_subarray(arr):

    max_sum = arr[0]
    sum = arr[0]
    for i in range(1,len(arr)-1):
        sum = max(arr[i],sum +arr[i])
        if sum > max_sum:
            max_sum = sum
    return max_sum

a = [-2,3,2,-1,-2,4,-3,4,6,-5,2,4,6,-8,-9,4,6,2,-6]
t_0 = time.perf_counter()
find_max_subarray(a)
t_1 = time.perf_counter()
t_total = t_1 - t_0

t_0_brute = time.perf_counter()
brute_force_find_max(a,0,len(a))
t_1_brute = time.perf_counter()
t_total_brute =t_1_brute-t_0_brute

plt.xlabel('Number of n')
plt.ylabel('Time')
x1 = [0,5]
y1 = [0,t_total]
x2 = [0,5]
y2 = [0,t_total_brute]
plt.plot(x1,y1,label = "max sum search o(n)")
plt.plot(x2,y2,label ="brute force O(n^2)")
#No matter how big the array is, sum search will always beat brute force out the gate.
plt.legend(loc = "upper left")
plt.show()