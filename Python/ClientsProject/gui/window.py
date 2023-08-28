import tkinter as tk

#creo ventana y ajusto tamaño
root = tk.Tk()
root.geometry("800x700")
root.title("Aplicación Clientes")


#creo titulo

label = tk.Label(root, text='Clientes', font=("Times New Roman",20))
label.pack()
















#Mantenemos la ventana abierta hasta que el ussuario la cierre
root.mainloop()    

