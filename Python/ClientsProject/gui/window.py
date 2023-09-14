
import tkinter as tk
from tkinter import ttk
from functools import partial

#creo ventana y ajusto tamaño

def submenuAdd(root, db):
    child_w = tk.Toplevel(root)
    child_w.geometry("500x500")
    child_w.title("Agregar tabla")
    
    
    #defino los widgets
    label_title_table = tk.Label(child_w, text="TItulo de tabla") #creo el label
    label_pk = tk.Label(child_w, text="Primary Key")#label de la pk
    label_type_pk = tk.Label(child_w, text="Tipo")#label de la pk
    title_box = tk.Entry(child_w)#pido el titulod e la tabla
    label_box = tk.Entry(child_w)#pido el pk de la tabla
    type_combo = ttk.Combobox(child_w, values=["INTEGER", "TEXT", "BLOB", "REAL", "NUMERIC"]) # creo la lista desplegable
    finish_button = tk.Button(child_w, text="Terminar", command=lambda:[db.createTable({"table_name":title_box.get(), "pk": label_box.get(), "pk_type": type_combo.get()}), child_w.destroy()])
    
    # Acomodo los widgets
    label_title_table.pack()
    title_box.pack()
    label_pk.pack()
    label_box.pack()
    label_type_pk.pack()
    type_combo.set("Elija el tipo")
    type_combo.pack()
    
    finish_button.pack(pady=40)
    



def menu(db):
    root = tk.Tk()
    root.geometry("800x700")
    root.title("Aplicacion CLientes")
    
    
    
    new_table_b = tk.Button(root, text="Crear Tabla", command=partial(submenuAdd, root, db))
    new_table_b.pack()
    
    

    
    
    root.mainloop()










 

