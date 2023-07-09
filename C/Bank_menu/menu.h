#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "estructuras.h"

//Creamos el menú principal por pantalla
void menu_opciones(struct Clientes c[],struct Binario b[]);



//submenu que se despliega al elegir la opcion LISTAR
void submenu_listar(struct Clientes c[], struct Binario b[],int *filas);


//submenu que se despliega al elegir la opcion BUSCAR
void submenu_buscar(struct Binario b[], int filas);
#endif // MENU_H_INCLUDED

