# https://www.hackerrank.com/challenges/one-month-preparation-kit-flipping-bits/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one

def flippingBits(n):
    bina = format(n, "#034b") #convierto a binario en formato 32 bits (2 mas por el 0b)
    binaFlip = str()          #string con el binario flipeado
    for x in bina[2:]:        #si hay un 0 en el binario original,pongo un 1 en el flipeado y viceversa
        if (x=="1"):
            binaFlip+='0'
        else:
            binaFlip+='1'
    binaFlip = int(binaFlip,2)
    return binaFlip
    
n = 0

print(flippingBits(n))