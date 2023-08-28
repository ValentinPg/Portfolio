import clases

def menu():
    print("--Bienvenido--")
    print('Ingrese una opción:\n1-Buscar Cliente\n2-Agregar Cliente\n0-Salir')
    op = int(input("->"))
    
    if op==1:
        name = input('Ingrese el apellido: ')
        surname = input('Ingrese el nombre: ')
        client = clases.Client(name,surname)
        print(client)
    if op==2:
        name = input('Ingrese el apellido: ')
        surname = input('Ingrese el nombre: ')
        client = clases.Client(name,surname)
        print(client)
    if op == 0:
        exit(0)
        
while 1:
    menu()
    