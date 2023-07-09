#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include "estructuras.h"

int leer_archivo(struct Clientes c[]); //funcion para parsear el csv

void cambio(); // formatea e archivo a csv "clásico"

void listar_txt(struct Clientes c[],int cantidadRegistrada); //imprime el csv por pantalla

void crear_dat();////crea el .dat, si ya existe lo sobreescribe

void migrar(struct Clientes c[], int cantidadRegistrada, struct Binario b[]); //migra al .dat los registros del txt

void actualizar_binario(struct Binario b[],int cantidadRegistrada); //funcion auxiliar para cargar los nuevos clientes al binario

void listar_dat(struct Binario b[],int *filas, int flag);//funcion que lista por pantalla el .dat

void listar_activos(struct Binario b[], int cantidadRegistrada);//lista los campos del binario activos nada mas

void listar_tipoCredito(struct Binario b[],int filas);// filtrado por un tipo de crédito que elija el usuario

void listar_mes(struct Binario b[],int filas);

void validar_binario(struct Binario b[], int filas); //me fijo si el archivo creditos.dat ya existe

void alta(struct Binario c[], int* filas);//funcion para dar de alta a un nuevo cliente

void modificar(struct Binario b[], int cantidadRegistrada);//funcion que me permite modificar algunos datos del ususario y lo carga nuevamente en el archivo binario


int busqueda_numero_orden(struct Binario b[], int filas);//busca el cliente por ID

int busqueda_apellido(struct Binario b[], int filas);//funcion que le pide al usuario un apellido y si lo encuentra lo imprime

void baja_logica(struct Binario b[], char nombreArchivo[]); //funcion que me permite dar de baja a un cliente (hace tambien la baja fisica automaticamente)

void baja_fisica(struct Binario b,FILE* binario, char str[]);//funcion que guarda los datos de un cliente inactivo en un .xyz

int listar_xyz(struct Binario b[], char nombreArchivo[]);//Recorro el csv modificado y guardo los datos de los clientes en un array de structs
#endif // ARCHIVOS_H_INCLUDED
#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED



#endif // ARCHIVOS_H_INCLUDED
