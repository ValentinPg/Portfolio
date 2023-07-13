# https://www.hackerrank.com/challenges/one-month-preparation-kit-countingsort1/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one

def countingSort(arr):
    sortArr = [0]*100   #creamos el array de 100 con todo ceros
    
    for i in arr:       #lleno el arary vacio con el indice de i
        sortArr[i]+=1
        
    return sortArr


arr = [1,1,1,5,2]

print(countingSort(arr))