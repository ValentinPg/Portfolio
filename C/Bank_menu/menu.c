//en este archivo irán las funciones correspondientes al menú del punto 1, el menu se ejecuta hasta que el usuario
//ingrese lo contrario.

#include <stdio.h>
#include <stdlib.h>
#include "validaciones.h"
#include "archivos.h"
#include "estructuras.h"



void submenu_listar(struct Clientes c[], struct Binario b[], int* filas)//submenu que se despliega al elegir la opcion LISTAR
{
    int n;
    listar_dat(b,filas,0);//cargo el archivo en memoria
    system("cls");//limpio la pantalla
    printf("\n\nINGRESE UNA OPCI%cN:\n",224);
    printf(" 0-Salir\n 1-Listar todos\n 2-S%clo el campo activo =1\n 3-Tipo de cr%cdito\n 4-Rango de tiempo\n\n\n-> ",162,130);
    scanf("%d",&n);
    fflush(stdin);

    //validamos el valor ingresado por el usuario
    validar_opcion(&n,0,5);

    //armamos el menú
    switch(n)
    {
    case 0:
        exit(0);                   //La opción sero siempre esta reservada para termiar el programa
        break;
    case 1:
        listar_dat(b,filas,1);     //listamos el archivo completo
        break;
    case 2:
        listar_activos(b,*filas);  //listamos únicamente los clientes con el el campo activo en 1
        break;
    case 3:
        listar_tipoCredito(b,*filas);//dejo al usuario elegir por cual tipo de crédito listar
        break;
    case 4:
        listar_mes(b,*filas);      //el usuario ingrese 2 fechas y listo los clientes que se encuentran en ese rango
        break;
    }
}

void submenu_buscar(struct Binario b[], int filas)          //submenú que se despliega al elejir la opció BUSCAR
{
    int n;

    //limpio la pantalla
    system("cls");

    printf("INGRESE UNA OPCI%cN:\n",224);
    printf(" 0-Salir\n 1-Nro de orden\n 2-Apellido\n\n\n-> ");
    scanf("%d", &n);
    fflush(stdin);

    //validamos el valor ingresado por el usuario
    validar_opcion(&n,0,2);


    //armamos el menú
    switch(n)
    {
    case 0:
        exit(0);                        //el 0 siempre es para abandonar el programa
        break;
    case 1:
        busqueda_numero_orden(b,filas); //el ususario ingresa el número de orden(ID) y, si el cliente existe, se imprime por pantalla
        break;
    case 2:
        busqueda_apellido(b,filas);     //el usuario ingresa el apellido y se lista al primer cliente con ese apellido (no es case sensitive)
        break;
    }

}




void menu_opciones(struct Clientes c[], struct Binario b[]) //Creamos el menú principal por pantalla, se ejecuta hasta que el usuario indique lo contrario
{
    //declaro las variables que va a usar la función
    int n;
    int filas,filasCSV;
    char nombreArchivoXYZ[50];



    //Para no trabajar directamente sobre el csv original, se crea un archivo csvFinal sobre el cual trabajar y se parsea desde ahi
    filas = leer_archivo(c);    //almaceno el numero de filas, me va a servir para recorrer el archivo y comprobar si hubo errores
                                //al leer o escribir datos

    filasCSV=filas;            //almaceno la cantidad de registros que tenia originalmente por si llega a haber alguna modificación



    validar_binario(b,filas);//me fijo si existe el arcivo binario

    printf("---BIENVENIDO----\n");
    do //Quiero que el menú se ejecute hasta que el usuario decida salir (opción 0)
    {
        printf("\nINGRESE UNA OPCI%cN:\n",224);
        printf(" 0-Salir\n 1-Listar txt\n 2-Crear\n 3-Migrar\n 4-Listar dat\n 5-Alta\n 6-Buscar\n 7-Modificar\n 8-Baja l%cgica\n 9-Listar xyz\n\n\n-> ",161);

        scanf("%d",&n);
        fflush(stdin);


        //validamos el valor ingresado por el usuario
        validar_opcion(&n,0,10);

        //armamos el menú
        switch(n)
        {
        case 0:
            exit(0);                //la opción 0 siempre es para salir
            break;
        case 1:
            listar_txt(c,filasCSV); //funcion encargada de imprimir el csv
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 2:
            crear_dat();          //crea el .dat, [CUIDADO!]: si ya existe lo borra.
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 3:
            migrar(c,filasCSV,b);  //copia los registros del .csv a un archivo binario (nombre default: "creditos.dat")
                                   //[CUIDADO!]: al migrar los datos se reescribe el creditos.dat anterior

            filas = filasCSV;      //a migrar el archivo .dat me va a quedar con el mismo numero de filas que el .csv fuente
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 4:
            submenu_listar(c,b,&filas);//invoca el submenú con las opciones para listar el .dat
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 5:
            alta(b,&filas);           //función que me permite dar de alta a un nuevo cliente
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 6:
            submenu_buscar(b,filas);  //función para invocar a un submenú con las opciones para buscar clientes
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 7:
            modificar(b,filas);      //función que me permite modificar algunos datos de un cliente ya dado de alta
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 8:
            baja_logica(b,nombreArchivoXYZ); //función que me permite dar de baja a un cliente (realiza tambien la baja física)
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;
        case 9:
            listar_xyz(b,nombreArchivoXYZ);  //lista el archivo de texto con las bajas hechas, en el se guardan los datos de
                                             //los clientes dados de baja
            printf("\nIngrese una tecla para continuar...\n");
            getchar();
            break;

        }
    }
    while (n!=0);

}





