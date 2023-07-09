#include <stdio.h>
#include <stdlib.h>
#define CANT 1000
#include "menu.h"
#include "validaciones.h"
#include "estructuras.h"

//---------------------------------------------------------------------------------------------------//

// Nombre y Apellido: Valentín Pugliese

//Fecha de entrega: 20/06/2023

//Archivos:archivos.c, menu.c, validaciones.c, main.c,archivos.h,estructuras.h,menu.h,validaciones.h,
//prestamos.csv, prestamosFinal.csv, creditos.dat, TP_Valentin_Pugliese.cbp


//----------------------------------------------------------------------------------------------------//
int main()
{
    //declaro los array de structs
    struct Clientes cliente[CANT];
    struct Binario binario[CANT];


    //PUNTO 1: Construir un menú de opciones para operar la aplicación. Cada opción debe identificar claramente la operación.//
    menu_opciones(cliente,binario);//invocamos en menu de opciones


    return 0;
}
