import copy
import random

class Hat:
    
    def __init__(self, **kwargs) -> None:
        #guardo el diccionario de kwargs por las dudas
        self.drawDict = kwargs
        
        #Lista que va  a contener el las bolas
        self.contents = list()
        
        #lleno la lista
        for key, value in kwargs.items():
            for _ in range(value):
                self.contents.append(key)
        
    #metodo que me devuelve un una lista con n bolas aleatorias
    def draw(self, n):
        #Me fijo si n suppera la longitud de mi lista
        if (n>len(self.contents)-1):
            return self.contents
        # Copio la lista
        copium = copy.deepcopy(self.contents)
        
        # Lista donde se van a guardar las bolas sacadas
        listPoped = list()
        
        # Lleno la lista n veces, popeo una posicion aleatoria de la lista copiada
        for _ in range(n):
            listPoped.append(self.contents.pop(random.randint(0,len(self.contents)-1)))
        return listPoped

#funcion que convierte una lista en diccionario
def convert(lista):
    miSet = set(lista)
    miDict = dict()
    for element in miSet:
        value = 0
        for i in range(len(lista)):
            if (element == lista[i]):
                value+=1
        miDict[element] = value
    return miDict
        
       
def experiment(hat, expected_balls, num_balls_drawn, num_experiments):
    cont = 0    #contador de coincidencias
    
    for _ in range(num_experiments):
        i=0     #contador de coincidencias dentro de cada caso
        case = copy.deepcopy(hat).draw(num_balls_drawn) #copiamos para no tener problemas con el draw (ya que me vacia el Hat)
        converted = convert(case) #convierto el la lista de las bolas en un diccionario para poder compararlo mas facilmente con el expected balls
        
        for key in expected_balls:
            # Si la key existe, comparo si es mayor o igual en mi draw
            if ((key in converted) and (converted[key]>=expected_balls[key])):
                i+=1    #si se cumple sumo uno a mi contador de draw
                
            # Si el contador de draws llegó a  la misma longitud que mi diccionario de expected, significa que todas las bolas de expected estan en el draw, por lo que puedo aumentar mi contador de coincidencias
            if (i== len(expected_balls)):
                cont+=1 
                break
        

    return cont/num_experiments