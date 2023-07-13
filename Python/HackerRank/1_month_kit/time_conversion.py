# https://www.hackerrank.com/challenges/one-month-preparation-kit-time-conversion/problem?h_l=interview&isFullScreen=true&playlist_slugs%5B%5D%5B%5D=preparation-kits&playlist_slugs%5B%5D%5B%5D=one-month-preparation-kit&playlist_slugs%5B%5D%5B%5D=one-month-week-one&h_r=next-challenge&h_v=zen&h_r=next-challenge&h_v=zen





#
# Complete the 'timeConversion' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#

def timeConversion(s):
    h,m,s = s.split(":")                #separo en horas, minutos y segundos
    if ((s[2]=='P') and (h!='12')):     #separo en 2 sets de casos, cuando es PM o AM y cuando h==12 o no
        h = int(h) + 12                 #si es PM le sumo 12 a la hora
        s = f"{h}:{m}:{s}"
        return s[0:8]
    elif ((s[2]=='A') and (h!="12")):
        s = f"{h}:{m}:{s}"             #si es AM lo dejo tal cual esta
        return s[0:8]
    elif ((s[2]=='A') and (h=="12")):   #ahora esta el caso en que la hora sea 12, sumar 12 no me sirve, tengo que cambiarlo por 00
        h = '00'
        s = f"{h}:{m}:{s}"
        return s[0:8]
    elif ((s[2]=='P') and (h=="12")):   #en este caso podria poner un else, pero asi me parece que qeuda mas clara la logica
        s = f"{h}:{m}:{s}"
        return s[0:8]
        

if __name__ == '__main__':
    

    s = input()
    
    result = timeConversion(s)

    print(result)
