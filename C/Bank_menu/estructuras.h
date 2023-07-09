#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED
#define TAM 250


struct Clientes
{
    int orden;
    char nombre[TAM];
    double importe;
    char tipoCredito[TAM];
    int dia;
    int mes;
    int anio;
    int nroCuotas;
    double importeCuota;
    double iva;
    double total;
    int activo;
};


struct Binario
{
    int orden;
    char nombre[TAM];
    char apellido[TAM];
    float importe;
    char tipoCredito[TAM];
    int dia;
    char mes[3];
    int anio;
    int nroCuotas;
    float importeCuota;
    float iva;
    float total;
    int activo;
};


#endif // ESTRUCTURAS_H_INCLUDED
