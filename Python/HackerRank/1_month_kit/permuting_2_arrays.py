# https://www.hackerrank.com/challenges/one-month-preparation-kit-two-arrays/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one

def twoArrays(k, A, B):
    A.sort()
    B.sort(reverse=True)
    for i in range(len(A)):
        if ((A[i]+B[i])<k):
            return "NO"
    return "YES"
    
A = [2,1,3]
B = [7,8,9]
k = 10

print(twoArrays(k,A,B))
