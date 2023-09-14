
import tkinter as tk
from tkinter import ttk
from functools import partial

#creo ventana y ajusto tamaño

def submenuAdd(root):
    child_w = tk.Toplevel(root)
    child_w.geometry("500x500")
    child_w.title("Agregar tabla")
    
    list_types = ["INTEGER", "TEXT", "BLOB", "REAL", "NUMERIC"]
    
    #defino los widgets
    label_title_table = tk.Label(child_w, text="TItulo de tabla") #creo el label
    label_pk = tk.Label(child_w, text="Primary Key")#label de la pk
    label_type_pk = tk.Label(child_w, text="Tipo")#label de la pk
    title_box = tk.Entry(child_w)#pido el titulod e la tabla
    label_box = tk.Entry(child_w)#pido el pk de la tabla
    type_combo = ttk.Combobox(child_w, values=list_types)
    finish_button = tk.Button(child_w, text="Terminar", command=lambda:print({"titulo":title_box.get(), "pk": label_box.get()}))
    
    # Acomodo los widgets
    label_title_table.pack()
    title_box.pack()
    label_pk.pack()
    label_box.pack()
    label_type_pk.pack()
    type_combo.set("Elija el tipo")
    type_combo.pack()
    
    finish_button.pack(pady=40)
    
    #tk.Button(child_w, text="Confirmar Titulo", command= lambda: print(title.get())).pack()


def menu():
    root = tk.Tk()
    root.geometry("800x700")
    root.title("Aplicacion CLientes")
    
    
    
    new_table_b = tk.Button(root, text="Crear Tabla", command=partial(submenuAdd, root))
    new_table_b.pack()
    
    

    
    
    root.mainloop()










 

