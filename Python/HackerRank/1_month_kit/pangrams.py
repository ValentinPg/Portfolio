
# https://www.hackerrank.com/challenges/one-month-preparation-kit-pangrams/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one

def pangrams(s):
    #lo pasamos a lowercase para evitar el case sensitive y sacamos los espacios
    s = s.lower()       
    s = s.replace(" ","")
    #ponemos todas las letras del abecedario en un set
    letters = set("abcdefghijklmnopqrstuvwxyz")
    #convertimos el string en set para eliminar las repeticiones
    miSet = set(s)
    #si la diferencia simetrica me da un set vacio signific que los sets son iguales, ergo, la palabra es un panagrama
    if (len(letters.symmetric_difference(miSet))==0):
        return "pangram"
    else:
        return "not pangram"
    
    
    

s = "We promptly judged antique ivory buckles for the prize"
print(pangrams(s))

    

