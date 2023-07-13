# https://www.hackerrank.com/challenges/one-month-preparation-kit-mini-max-sum/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one&h_r=next-challenge&h_v=zen
import math
import os
import random
import re
import sys

#
# Complete the 'miniMaxSum' function below.
#
# The function accepts INTEGER_ARRAY arr as parameter.
#

def miniMaxSum(arr):
    maxSum = 0
    minSum = 0
    
    #ordeno el array de manera ascendente
    arr.sort()

    #sumo los 1eros 4, meno el ultimo que es el mayor
    for i in range((len(arr)-1)):
        minSum+=arr[i]
    
    #orden el array de manera descendente
    arr.sort(reverse=True)

    #sumo los 1eros 4, meno el ultimo que es el menor
    for i in range((len(arr)-1)):
        maxSum+=arr[i]
        
    print(f"{minSum} {maxSum}")

if __name__ == '__main__':

    arr = list(map(int, input().rstrip().split()))

    miniMaxSum(arr)
