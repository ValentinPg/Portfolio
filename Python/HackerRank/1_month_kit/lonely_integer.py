# https://www.hackerrank.com/challenges/one-month-preparation-kit-lonely-integer/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one&h_r=next-challenge&h_v=zen

def lonelyinteger(a):
    miSet = set(a)  #obtengo un set con todos los elementos unicos
    flag = 0        #esta va a ser mi contador que checkea cuantas veces se repite
    for n in miSet: #reviso por cada elmento del set todos los elementos del array y comparo
        flag = 0
        for y in a:
            if(n==y):
                flag+=1
        if (flag == 1): #me fijo si el flag se encendio solo una vez, si es asi significa que ese es el elemento uico del array
            return n
    
a = [1,2,3,4,3,2,1]

print(lonelyinteger(a))
                    