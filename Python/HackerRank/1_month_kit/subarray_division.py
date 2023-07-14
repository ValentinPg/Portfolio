# https://www.hackerrank.com/challenges/one-month-preparation-kit-the-birthday-bar/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one

def birthday(s, d, m):
    i = 0
    j = m
    cont = 0
    
    while (i<len(s)):
        if (sum(s[i:j])==d):
            cont+=1
        i+=1
        j+=1
    return cont



s = [2,2,1,3,2]

d = 4

m = 2

print(birthday(s,d,m))