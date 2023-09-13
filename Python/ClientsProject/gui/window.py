import tkinter as tk
from functools import partial

#creo ventana y ajusto tamaño

def submenuAdd(root):
    child_w = tk.Toplevel(root)
    child_w.geometry("500x500")
    child_w.title("Agregar tabla")


def menu():
    root = tk.Tk()
    root.geometry("800x700")
    root.title("Aplicacion CLientes")
    
    new_table_b = tk.Button(root, text="Crear Tabla", command=partial(submenuAdd, root))
    new_table_b.pack()
    
    
    
    root.mainloop()







def submenuAdd(root):
    child_w = tk.Toplevel(root)
    child_w.geometry("500x500")
    child_w.title("Agregar tabla")


 

