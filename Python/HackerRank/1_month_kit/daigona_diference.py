# https://www.hackerrank.com/challenges/one-month-preparation-kit-diagonal-difference/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one

def diagonalDifference(arr):
    dim = len(arr)  #guardo la dimension del la amtriz, al ser cuadrada tiene la misma cantidad de filas que de columnas
    
    #acumuladores
    sumLD = 0
    sumRD = 0
    
    #sumo la primera diagonal, los indices de filas y columnas van de la mano
    for i in range(dim):
        sumLD+=arr[i][i]
    
    j = dim-1 #contador para las columnas, que en el caso de la diagonal derecha van en orden descendente
    
    #sumo la daigonal derecha
    for i in range(dim):
        sumRD+=arr[i][j]
        j-=1
    
    return (abs(sumLD-sumRD))
    
arr = [
    [11,2,4],
    [4,5,6],
    [10,8,-12]
]

print(diagonalDifference(arr))