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
    cont = 0
    for _ in range(num_experiments):
        case = hat.draw(num_balls_drawn)
        try:
            converted = convert(case)
            for key in expected_balls:
                if (converted[key]>=expected_balls[key]):
                    cont+=1
        except KeyError:
            continue
        
    return cont/num_experiments