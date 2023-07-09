#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                                      |VALIDACIÓN|
void validar_opcion(int *n, int min, int max); //valida que el numero que le paso este en el intervalo señalado

void validar_opcion_float(float *n, int min, int max); //idem Validar Opcion, pero con valores del tipo float

void validar_texto(char texto[]); //Revisa que el string pasado no contenga números

int errores(int n); //control de errores



//***********************************************************************************************************************************
//                                  |FUNCIONES AUXILIARES|
void separar(char nombreYApellido[], char nombre[], char apellido[]); //Función que separa el nombre y apellido del cliente

void capitalizar(char palabra[]); //convierte un string en mayusculas

void conversor_mes(int n, char c[]); //devuleve un mes en 3 letras en funcion del numero que se le pase

void tiempoAhora_string(char dia[], char mes[], char anio[]); //calcula el teimpo en este instante y lo devuelve en 3 strings

void tiempoAhora_int(int* dia, int* mes, int* anio);//calcula el tiempo en este instante y lo devuelve en 3 ints




#endif // VALIDACIONES_H_INCLUDED

