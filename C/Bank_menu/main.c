#include <stdio.h>
#include <stdlib.h>
#define CANT 1000
#include "menu.h"
#include "validaciones.h"
#include "estructuras.h"

//---------------------------------------------------------------------------------------------------//

// Nombre y Apellido: Valent�n Pugliese

//Fecha de entrega: 20/06/2023

//Archivos:archivos.c, menu.c, validaciones.c, main.c,archivos.h,estructuras.h,menu.h,validaciones.h,
//prestamos.csv, prestamosFinal.csv, creditos.dat, TP_Valentin_Pugliese.cbp


//----------------------------------------------------------------------------------------------------//
int main()
{
    //declaro los array de structs
    struct Clientes cliente[CANT];
    struct Binario binario[CANT];


    //PUNTO 1: Construir un men� de opciones para operar la aplicaci�n. Cada opci�n debe identificar claramente la operaci�n.//
    menu_opciones(cliente,binario);//invocamos en menu de opciones


    return 0;
}
