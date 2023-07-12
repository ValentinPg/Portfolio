# https://www.hackerrank.com/challenges/one-month-preparation-kit-plus-minus/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one
import math
import os
import random
import re
import sys

#
# Complete the 'plusMinus' function below.
#
# The function accepts INTEGER_ARRAY arr as parameter.
#

def plusMinus(arr):
    long = len(arr)
    posFlag = 0
    negFlag = 0
    zeroFlag = 0
    
    for n in arr:
        if (n>0):
            posFlag+=1
        elif (n==0):
            zeroFlag+=1
        else:
            negFlag+=1
    pos = posFlag/long
    zero = zeroFlag/long
    neg = negFlag/long
    print("{0}\n{1}\n{2:.6f}".format(pos,neg,zero))
    

if __name__ == '__main__':

    arr = [-4, 3, -9, 0, 4, 1]

    plusMinus(arr)
