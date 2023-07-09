//-----------------------------------------------------------------------------------------------------------------------------
//archivo que contiene las funciones para validar datos de entrada y funciones auxiliares que realizan procesos repetitivos
//Además contiene el control de errores
//Más detalle sobre cada función en el PDF con la documentación
//-----------------------------------------------------------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                      |VALIDACIÓN|

//comprueba que el numero que le paso este en el intervalo señalado
void validar_opcion(int *n, int min, int max)
{

//  Si el numero ingresado no esta entre el rengo indicado entra en un loop que me vuelve a pedir el dato infinitamente
    while ((*n<min) || (*n>max))
    {
        printf("\n-> ");
        scanf("%d",n);
        fflush(stdin);
    }
}

//idem Validar Opcion, pero con valores del tipo float
void validar_opcion_float(float *n, int min, int max)
{


    while ((*n<min) || (*n>max))
    {

        printf("\n-> ");
        scanf("%f",n);
        fflush(stdin);

    }
}

//Revisa que el string pasado no contenga números
void validar_texto(char texto[])
{
    int flag=0; //bandera que me va a avisa si hubo un caracter no permito en el texto


//      Reviso el texto cáracter por cáracter
        for (int letra=0; letra<=(sizeof(texto)); letra++)
        {
            // me fijo si es el final, si lo es dejo de comparar
            if(texto[letra]=='\0')
               {
                   break;
               }
            //si esl caracter es un número enciendo el flag
            if ((texto[letra]>=48)&&(texto[letra]<=57))
            {
                flag =1;
            }

        }

// si el flag se encendió siginifica que algo no anduvo bien, por lo tanto le pido al usuario que lo vuelva a ingresar

    while(flag==1)
    {
        flag = 0; //reseteo el flag

        printf("El texto debe contener unicamente letras:\n->");
        gets(texto);
        fflush(stdin);

        //Repito el proceso que realicé anteriormente para comprobar
        for (int letra=0; letra<=(sizeof(texto)); letra++)
        {
            if(texto[letra]=='\0')
               {
                   break;
               }
            if ((texto[letra]>=48)&&(texto[letra]<=57))
            {
                flag =1;
            }

        }

    }

}



//Array que contiene los mensajes de error
int errores(int n) //controlamos los errores con un array
{
    char *c[] =
    {
        "\n---ERROR! NO SE PUEDE DIVIR POR 0",
        "\n---ERROR! NO SE PUDO ABRIR EL ARCHIVO",
        "\n---ERROR! NO SE PUDO PARSEAR EL ARCHIVO",
    };


    printf("%s",c[n]);
    exit(-n);
}



//***********************************************************************************************************************************
//                                  |FUNCIONES AUXILIARES|


//Función que separa el nombre y apellido del cliente
void separar(char nombreYApellido[], char nombre[], char apellido[])
{
    //copio el nombre y apellido originales para no separarlos por error
    strcpy(nombre,nombreYApellido);
    //creo el token y separo el nombre del cliente
    char *token = strtok(nombre," ");

    //uso un ciclo para separar el apellido en una sola variable
    while(token!=NULL)
    {
        strcpy(apellido,token);
        //no quiero separar el apellido porque algunos tienen espacios
        token = strtok(NULL, "");
    }

}

//Función que convierte un texto a mayúsculas
void capitalizar(char palabra[])
{
    int i=0;
    while(palabra[i]!='\0')
    {
        palabra[i]=toupper(palabra[i]);
        i++;
    }
}

//Convierte un numero pasado a un texto de 3 letras con el mes correspondiente
void conversor_mes(int n, char c[])
{
    switch(n)
    {
    case 1:
        strcpy(c,"ene");
        break;
    case 2:
        strcpy(c,"feb");
        break;
    case 3:
        strcpy(c,"mar");
        break;
    case 4:
        strcpy(c,"abr");
        break;
    case 5:
        strcpy(c,"may");
        break;
    case 6:
        strcpy(c,"jun");
        break;
    case 7:
        strcpy(c,"jul");
        break;
    case 8:
        strcpy(c,"ago");
        break;
    case 9:
        strcpy(c,"sep");
        break;
    case 10:
        strcpy(c,"oct");
        break;
    case 11:
        strcpy(c,"nov");
        break;
    case 12:
        strcpy(c,"dec");
        break;
    }
}

//calcula el tiempo en este instante y lo devuelve en 3 strings
void tiempoAhora_string(char dia[],char mes[], char anio[])
{
    time_t ahora = time(NULL); //guardo la hora en UNIX
    struct tm fecha=*localtime(&ahora); //declaro el struct con el horario actual, me va a permitir acceder al dia, hora, año, etc.


    sprintf(dia,"%02d",fecha.tm_mday);
    sprintf(mes,"%02d",fecha.tm_mon+1);
    sprintf(anio,"%02d",fecha.tm_year+1900);





}

//calcula el tiempo en este instante y lo devuelve en 3 ints
void tiempoAhora_int(int* dia, int* mes, int* anio)
{
    time_t ahora = time(NULL); //guardo la hora en UNIX
    struct tm fecha=*localtime(&ahora); //declaro el struct con el horario actual, me va a permitir acceder al dia, hora, año, etc.

    *dia=fecha.tm_mday;
    *mes=fecha.tm_mon+1;
    *anio=fecha.tm_year+1900;


}

