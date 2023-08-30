import sqlite3
import os

class Client():
    
    def __init__(self, name='NULL', surname='NULL', dni='NULL') -> None:
        self.name = name
        self.surname = surname
        self.dni = dni
    
    
    def clientInfo(self):
        return {'name' : self.name, 'surname' : self.surname, 'dni' : self.dni}
    
    def __str__(self) -> str:
        return f'Cliente {self.surname} {self.name}'
    
    
class Menu():
    
    def __init__(self, client) -> None:
        self.client = client
    
    # Metodo para cargar los datos del cliente
    def clientData(self):
        self.client.surname = input("Ingrese el nombre del cliente: ")
        self.client.name = input("Ingrese el apellido del cliente: ")
        self.client.dni = input("INgrese el DNI del cliente (sin puntos): ")
        
    # metodo para crear un nuevo cliente en la base de datos
    def newClient(self):
        pass
    
    
    # Metodo temporal, tiene que haber vario9s tipos de busqueda
    def searchClient(self):
        pass


class DataBase():
    
    #cada vez que cree el objeto base de datos voy a querer que me conecte con 'clients.db'
    def __init__(self) -> None:
        db_path = (os.path.join(os.getcwd(),'Python','ClientsProject','db','clients.db')) #obtengo el path de la carpeta db y le agrego la db
        try:
            conn = sqlite3.connect(db_path)
        except Exception():
            return 'Error al conectar co la base de datos'
        
        self.c = conn.cursor()
        
        
        #deberia trabajar con diccionarios? LIstas? o Tuplas?
    def createTable(self, diccionario):
        self.c.execute(f'''
                       CREATE TABLE if not exists {diccionario['table_name']}(
                           placeholder int
                       ) 
                       ''')
        
