import tkinter as tk

#creo ventana y ajusto tamaño

class App():
    
    def __init__(self) -> None:
        self.root = tk.Tk()
        self.root.geometry("800x700")
        self.root.title("Aplicación Clientes")
        
        self.title()
        self.button_new_table()

    def title(self):
        label = tk.Label(self.root, text='Clientes', font=("Times New Roman",20))
        
    def button_new_table(self):
        new_table_b = tk.Button(self.root, text="Crear Tabla")
        new_table_b.pack()





















#Mantenemos la ventana abierta hasta que el ussuario la cierre
 

