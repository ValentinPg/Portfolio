import clases

def menu():
    clases.DataBase()
    print("--Bienvenido--")
    print('Ingrese una opción:\n1-Buscar Cliente\n2-Agregar Cliente\n0-Salir')
    op = int(input("->"))
    client =  clases.Client()
    menu = clases.Menu(client)
    
    if op==1:
        menu.clientData()   #cargo los datos del cliente
        menu.searchClient() #llamo al metodo de busqueda
        print(client)
    if op==2:
        menu.newClient()    #llamo al metodo de busqueda
        print(client)
    if op == 0:
        exit(0)
        
while 1:
    menu()
    