//Acá se encuentran las funciones para manipular archivos, osea casi todas las funcione del TP
//Más detalle sobre cada función en la documentación

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "estructuras.h"
#include "validaciones.h"
#define TAM 250


//FUNCIONES PARA TRABAJAR CON EL TXT

//Punto 4//
void listar_txt(struct Clientes c[],int cantidadRegistrada) //imprime el listado del csv
{

    printf("Orden\t  Cliente\t  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota\n\n",164);
    for (int i=1; i<cantidadRegistrada; i++)//cantidadRegistrada es la cantidad de filas del csv
    {
        printf("%3d| %20s %8.2lf  %14s \t %02d %02d %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf\n", c[i].orden, c[i].nombre, c[i].importe, c[i].tipoCredito, c[i].dia, c[i].mes, c[i].anio, c[i].nroCuotas, c[i].importeCuota, c[i].iva, c[i].total);
    }
}


void cambio() //esta funcion copia los datos del prestamos.csv a un nuevo archivo cambiando los ';' por ',' y las ',' por '.'
{
    FILE* temp; //puntero del archivo prestamoFinal
    FILE *archivo;  //puntero de prestamos.csv
    char c;


    // Abro los archivos
    temp=fopen("prestamosFinal.csv", "w");
    archivo = fopen("prestamos.csv","r");


    // Reviso que no haya habido ningún error al abrir el archivo
    if (temp==NULL || archivo==NULL)
    {
        errores(1);
    }

    //tomamos el prier char del archivo original
    c = fgetc(archivo);

    //Recorro el archivo mientras no llegue al final
    while (c != EOF)
    {

        //Cambio las comas y punto-comas
        if (c==',')
            fputc('.',temp);
        else if(c==';')
            fputc(',',temp);
        else
            fputc(c,temp);

        c = fgetc(archivo);
    }

    //Cierro los archivos
    fclose(archivo);
    fclose(temp);

}


int leer_archivo(struct Clientes c[]) //Recorro el csv modificado y guardo los datos de los clientes en un array de structs
{
    cambio(); // copio el csv prestamos y lo modifico

    FILE *archivo; //puntero de mi archivo
    int leido=0; //variable para verificar que el scnaf este leyendo bien
    int i=0; //contador de ciclos
    char ca;//auxiliar para guardar un caracter


    //abro el archivo
    archivo=fopen("prestamosFinal.csv","r");


    //verífico que se este abriendo el archivo
    if (archivo==NULL)
    {
        errores(1);
    }

    do
    {
        //"elimino" los encabezados (no los tengo en cuenta)
        if (i==0)
        {
            ca=fgetc(archivo);
            while(ca!='\n')
            {
                ca=fgetc(archivo);
            }
            leido=11;

        }
        else
        {
            //parseo el archivo y verifico que se hayan leido las 11 columnas
            leido = fscanf(archivo,"%d,%249[^,],%lf,%249[^,],%d,%d,%d,%d,%lf,%lf,%lf\n", &c[i].orden, c[i].nombre, &c[i].importe, c[i].tipoCredito, &c[i].dia, &c[i].mes, &c[i].anio, &c[i].nroCuotas, &c[i].importeCuota, &c[i].iva, &c[i].total);
            c[i].activo=1; //asumo que todos los clientes estan activos

        }
        if (leido==11) //si se parsearon las 11 columnas bien, continuo con la fila siguiente
        {

            i++;
        }
        else //si hubo algun error al parsear el archivo devuelvo el error correspondiente
        {
            errores(2);
        }

    }
    while (!feof(archivo)); //recorro el archivo hasta que llegue al final

    fclose(archivo);

    //devuelvo la cantida de filas parseadas
    return i;

}


//FUNCIONES PARA TRABAJAR CON BINARIO (creditos.dat)

//PUNTO 5//
void crear_dat() //crea el .dat, si ya existe lo sobreescribe
{
    FILE* archivo;
    char r;

    //pido confirmacion por las dudas de que el usuario no haya presionado por erro
    printf("ADVERTENCIA: Si el archivo ya fue creado ese es sobreescrito\nEsta seguro de que desea continuar? [y/n]\n->");
    scanf("%c",&r);
    fflush(stdin);

    if ((r=='y')||(r=='Y'))
    {
    archivo=fopen("creditos.dat", "wb"); //creamos un archivo binario con el write, si ya existe lo borra

    if (archivo==NULL) //prueba a ver si hay errores al crear el archivo
    {
        errores(1);
    }

    printf("\nARCHIVO CREADO CORRECTAMENTE! ('creditos.dat')\n"); //aviso que se creo correctamente
    fclose(archivo);
    }
}


//PUNTO 6//
void lleno_binario(struct Clientes c[], struct Binario b[], int pos)//Función que copia los datos del sctruct del archivo de texto, al struct del archivo binario
{
    //copiamos el orden
    b[pos].orden=c[pos].orden;
    //vamos a separa nombre y apellido y masyusculizamos el apellido
    separar(c[pos].nombre,b[pos].nombre,b[pos].apellido);
    capitalizar(b[pos].apellido);
    //copiamos el importe
    b[pos].importe = c[pos].importe;
    //masyusculizamos y copiamos el tipo de credito
    strcpy(b[pos].tipoCredito,c[pos].tipoCredito);
    capitalizar(b[pos].tipoCredito);
    //copio el dia
    b[pos].dia = c[pos].dia;
    //copio el mes, pero en letras
    conversor_mes(c[pos].mes,b[pos].mes);
    //copio el año
    b[pos].anio = c[pos].anio;
    //copio las cuotas
    b[pos].nroCuotas=c[pos].nroCuotas;
    //copio los importes
    b[pos].importeCuota=c[pos].importeCuota;
    //copio el iva
    b[pos].iva=c[pos].iva;
    //copio el total
    b[pos].total=c[pos].total;
    //copio el estado
    b[pos].activo=c[pos].activo;


}

void migrar(struct Clientes c[], int cantidadRegistrada, struct Binario b[],int*filas)//migro los datos del csv a un .dat
{
    FILE *archivo;

    char r;

    //pido confirmacion por las dudas de que el usuario no haya presionado por erro
    printf("ADVERTENCIA: Si el archivo ya fue creado ese es sobreescrito\nEsta seguro de que desea continuar? [y/n]\n->");
    scanf("%c",&r);
    fflush(stdin);

    if ((r=='y')||(r=='Y'))
    {

    archivo = fopen("creditos.dat","wb"); //creo el .dat por las dudas, y ya existe lo sobreescribe

    //me fijo que no haya errores
    if (archivo ==NULL)
    {
        errores(1);
    }

    for (int i=1; i<cantidadRegistrada; i++)
    {
        //modifico los datos antes de pasarlo a binario
        lleno_binario(c,b,i);
        fwrite(&b[i],sizeof(struct Binario),1,archivo);
    }


    fclose(archivo);

    printf("\nMIGRACION EXITOSA\n");

    }

}


//PUNTO 7//
void listar_dat(struct Binario b[], int *filas, int flag) //imprime el .dat por pantalla
{
    FILE *archivo;
    int j=0; //este va  a ser mi indice
    archivo = fopen("creditos.dat","rb");

    //me fijo que no haya errores al abrir
    if (archivo == NULL)
    {
        errores(1);
    }

    while(!(feof(archivo)))
    {
        j++;//aumento el contador de filas
        //leo y lo guardo en el struct
        fread(&b[j],sizeof(struct Binario),1,archivo);

    }
    fclose(archivo);

    *filas = j; //seteo la cantidad de filas registradas en el binario
//  Imprimo los encabezados

    if (flag==1) //si el flag=1 siginifica que esta hablitada la impresión
    {
    printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
    //imprimo lo que cargué en el struct
    for(int pos=1; pos<*filas; pos++)
    {
        printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[pos].orden,b[pos].nombre,b[pos].apellido,b[pos].importe,b[pos].tipoCredito,b[pos].dia,b[pos].mes,b[pos].anio,b[pos].nroCuotas,b[pos].importeCuota,b[pos].iva,b[pos].total,b[pos].activo);
    }
    }
}


void listar_activos(struct Binario b[], int cantidadRegistrada)//filtrado por los clientes con el campo en activo=1
{
    system("cls");
    FILE* archivo;
    archivo=fopen("creditos.dat","rb");


    if (archivo==NULL) //revisamos que se haya abierto bien
        errores(1);

    //encabezados
    printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
    for (int pos=1; pos<cantidadRegistrada; pos++)
    {
        if(b[pos].activo==1)
            printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[pos].orden,b[pos].nombre,b[pos].apellido,b[pos].importe,b[pos].tipoCredito,b[pos].dia,b[pos].mes,b[pos].anio,b[pos].nroCuotas,b[pos].importeCuota,b[pos].iva,b[pos].total,b[pos].activo);
    }
}

void listar_tipoCredito(struct Binario b[],int filas) // filtrado por un tipo de crédito que elija el usuario
{
    int n;
    system("cls");

    //le voy a dar un menu de opciones para que el usaurio elija la el tipo de credito que desea filtrar
    printf("\nIndique el tipo de credito por el que desea filtrar:\n1-A sola firma\t2-Con Garantia\n->");
    scanf("%d",&n);
    fflush(stdin);

    //valido que la opcion sea válida
    validar_opcion(&n,1,2);
// encabezados
    printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
    //filtro usando un switch
    switch(n)
    {
    case 1:
        for (int i=1; i<filas; i++)
        {
            if(!(strcmp("A SOLA FIRMA",b[i].tipoCredito)))
                printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[i].orden,b[i].nombre,b[i].apellido,b[i].importe,b[i].tipoCredito,b[i].dia,b[i].mes,b[i].anio,b[i].nroCuotas,b[i].importeCuota,b[i].iva,b[i].total,b[i].activo);
        }
        break;
    case 2:
        for (int i=1; i<filas; i++)
        {
            if(!(strcmp("CON GARANTIA",b[i].tipoCredito)))
                printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[i].orden,b[i].nombre,b[i].apellido,b[i].importe,b[i].tipoCredito,b[i].dia,b[i].mes,b[i].anio,b[i].nroCuotas,b[i].importeCuota,b[i].iva,b[i].total,b[i].activo);
        }
        break;
    }
}


void validar_binario(struct Binario b[], int filas) //checkea si existe el archivo creditos.dat, si existe lo carga en memoria
{
    FILE* archivo;

    archivo=fopen("creditos.dat","r");

    if (archivo)
    {
        listar_dat(b,&filas,0);
    }
}


void listar_mes(struct Binario b[],int filas)
{
    system("cls");
    int minDia,minMes,minAnio,maxDia,maxMes,maxAnio,ahoraMes;

    //pido que ingrese el rango de tiempo
    printf("Ingrese el rango de tiempo:\n");
    printf("--DESDE--\n");
    printf("Ingrese el dia:\n->");
    scanf("%d",&minDia);
    fflush(stdin);
    validar_opcion(&minDia,1,31);

    printf("Ingrese el mes:\n->");
    scanf("%d",&minMes);
    fflush(stdin);
    validar_opcion(&minMes,1,12);

    printf("Ingrese el a%co:\n->",164);
    scanf("%d",&minAnio);
    fflush(stdin);
    validar_opcion(&minAnio,2000,2100);

//pido rango de teimpo maximo
    printf("--HASTA--\n");
    printf("Ingrese el dia:\n->");
    scanf("%d",&maxDia);
    fflush(stdin);
    validar_opcion(&minDia,1,31);

    printf("Ingrese el mes:\n->");
    scanf("%d",&maxMes);
    fflush(stdin);
    validar_opcion(&minMes,1,12);

    printf("Ingrese el a%co:\n->",164);
    scanf("%d",&maxAnio);
    fflush(stdin);
    validar_opcion(&minAnio,2000,2100);

    printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
    //recorro el array de structs y comparo
    for (int i=1; i<filas; i++)
    {
        //paso el mes a entero
        if (strcmp(b[i].mes,"ene")==0)
            ahoraMes=1;
        else if(strcmp(b[i].mes,"feb")==0)
            ahoraMes=2;
        else if(strcmp(b[i].mes,"mar")==0)
            ahoraMes=3;
        else if(strcmp(b[i].mes,"abr")==0)
            ahoraMes=4;
        else if(strcmp(b[i].mes,"may")==0)
            ahoraMes=5;
        else if(strcmp(b[i].mes,"jun")==0)
            ahoraMes=6;
        else if(strcmp(b[i].mes,"jul")==0)
            ahoraMes=7;
        else if(strcmp(b[i].mes,"ago")==0)
            ahoraMes=8;
        else if(strcmp(b[i].mes,"sep")==0)
            ahoraMes=9;
        else if(strcmp(b[i].mes,"oct")==0)
            ahoraMes=10;
        else if(strcmp(b[i].mes,"nov")==0)
            ahoraMes=11;
        else if(strcmp(b[i].mes,"dic")==0)
            ahoraMes=12;


        //imprimo los resultados que coinciden en pantalla
        if((b[i].dia>=minDia)&&(ahoraMes>=minMes)&&(b[i].anio>=minAnio))
        {
            if ((b[i].dia<=maxDia)&&(ahoraMes<=maxMes)&&(b[i].anio<=maxAnio))
                printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[i].orden,b[i].nombre,b[i].apellido,b[i].importe,b[i].tipoCredito,b[i].dia,b[i].mes,b[i].anio,b[i].nroCuotas,b[i].importeCuota,b[i].iva,b[i].total,b[i].activo);
        }
    }

}

//PUNTO 8//
void actualizar_binario(struct Binario b[],int cantidadRegistrada) //funcion auxiliar para cargar los nuevos clientes al binario
{
    FILE *archivo;

    archivo = fopen("creditos.dat","wb");

    //me fijo que no haya errores
    if (archivo ==NULL)
    {
        errores(1);
    }


    //vuelvo a cargar TODOS los structs al binario
    for (int i=1; i<cantidadRegistrada; i++)
    {
        fwrite(&b[i],sizeof(struct Binario),1,archivo);
    }

    fclose(archivo);
    printf("\nOperacion realizada correctamente!\n");
}
void alta(struct Binario c[], int* filas) //funcion para dar de alta a un nuevo cliente
{
    //defino todas las variables que voy a usar
    FILE* archivo;
    int n;
    char op;
    int id;
    int dia;
    int mes;
    int anio;



    archivo=fopen("prestamosFinal.csv","rb");
    system("cls");//limpio la pantalla

    //valido que el archivo se abra bien
    if (archivo==NULL)
    {
        errores(1);
    }

    //voy a permitir que se carguen mas de un cliente seguidos, para luego optimizar la carga al archivo .dat
    do
    {
        printf("Ingrese el ID del cliente:\n->");
        scanf("%d",&id);
        fflush(stdin);

        //No logré hacer que el acceso de comprobación sea directo, por lo que usé la forma tradiional y lo comparé con
        //donde debería estar en el array de structs si existiese
        while(c[id].orden || (id<=0))
        {
            //si ya existe o es menor a 0 obligo al usuario a que reingrese el ID
            printf("El id del cliente ingresado ya se encuentra en la base de datos o es un numero menor o igual a 0"
                   "\nPor favor vuelva a ingresarlo:\n->");
            scanf("%d",&id);
            fflush(stdin);
        }

        //al agregar datos voy a tener que actualizar el numero de filas del .dat
        if (id>=*filas)
            *filas = id+1;

        //una vez validado el ID puedo ya cargarlo
        c[id].orden = id;

        printf("Ingrese el nombre del cliente:\n->");
        gets(c[id].nombre);
        fflush(stdin);
        validar_texto(c[id].nombre); //me fijo que el nombre no tenga numeros

        printf("Ingrese el apellido del cliente:\n->");
        gets(c[id].apellido);
        fflush(stdin);
        capitalizar(c[id].apellido);
        validar_texto(c[id].apellido);//me fijo que el apellido no tenga numeros

        printf("Ingrese el importe del credito:\n->");
        scanf("%f",&c[id].importe);
        fflush(stdin);
        validar_opcion_float(&c[id].importe,1,99999);//me fijo que sea un numero y qeu no sea negativo

        //le hago elegir el tipo de credito con un menu para evitar errores de tipeo
        printf("Ingrese el tipo de credito:\n1-A sola firma\n2-Con garantia\n->");
        scanf("%d",&n);
        fflush(stdin);
        //valido que la opcion sea válida
        validar_opcion(&n,1,2);

        switch(n)
        {
        case 1:
            strcpy(c[id].tipoCredito,"A SOLA FIRMA");
            break;
        case 2:
            strcpy(c[id].tipoCredito,"CON GARANTIA");
            break;
        }

        tiempoAhora_int(&dia,&mes,&anio); //calculo la fecha en el instante en el que se da el alta

        c[id].dia=dia;
        c[id].anio=anio;
        conversor_mes(mes, c[id].mes); //convierto el mes a texto


        printf("Ingrese el numero de cuotas a pagar:\n->");
        scanf("%d",&c[id].nroCuotas);
        fflush(stdin);

        //seteo al usuario como activo
        c[id].activo=1;

        //calculo el imprte del credito
        c[id].importeCuota=c[id].importe/c[id].nroCuotas;

        //calculo los impuestos del importe de la cuota
        c[id].iva = c[id].importeCuota*0.21;

        //calculo el totañ de la cuota + impuestos
        c[id].total = c[id].importeCuota+c[id].iva;



        //le pregunto si quiere seguir cargando mas clientes
        printf("\n¿Desea seguir ingresando clientes?[y/n]\n");
        scanf("%c",&op);
        fflush(stdin);
    }
    while((op=='y')||(op=='Y'));

    fclose(archivo);

    //actualizo el binario con los nuevos clientes y los inserto donde corresponden
    actualizar_binario(c,*filas);

}




//PUNTO 10// SE PUEDE MODIFICAR SI LLEGO CON EL TIEMPO
void modificar(struct Binario b[], int cantidadRegistrada) //funcion que me permite modificar algunos datos del ususario y lo carga nuevamente en el archivo binario
{
    int orden; //variable que almacena el id
    float importe;//variable que almacena el nuevo importe
    char r;
    int n;
    char tipoCredito[75];


    printf("Igrese el ID del usuario que dessea modificar:\n->");
    scanf("%d",&orden);
    fflush(stdin);
    validar_opcion(&orden,1,cantidadRegistrada+1000);//quiero que el usuasrio ingrese un numero, no una letra

    //busco el cliente
    for (int i=1; i<cantidadRegistrada; i++)
    {

        if(b[i].orden == orden)
        {
            //Una vez encontrado pregunto el nuevo importe y el nuevo tipo de credito
            printf("\nUsted esta seleccionando al cliente: %s %s",b[i].nombre,b[i].apellido);
            printf("\nIngrese el nuevo importe:\n->");
            scanf("%f",&importe);
            fflush(stdin);
            validar_opcion_float(&importe,1,999999); //me fijo que nuevo importe sea un numero

            //le hago elegir el tipo de credito con un menu para evitar errores de tipeo
            printf("Ingrese el tipo de credito:\n1-A sola firma\n2-Con garantia\n->");
            scanf("%d",&n);
            fflush(stdin);
            //valido que la opcion sea válida
            validar_opcion(&n,1,2);

            switch(n)
            {
            case 1:
                strcpy(tipoCredito,"A SOLA FIRMA");
                break;
            case 2:
                strcpy(tipoCredito,"CON GARANTIA");
                break;
            }

            //le pido que me confirme
            printf("Esta seguro que desea realizar la modificacion? [y/n]:\n->");
            scanf("%c",&r);
            fflush(stdin);

            if((r=='y')||(r=='Y'))
            {
                //Ya modifico los tructs y reescribo el archivo csv
                b[i].importe = importe;
                strcpy(b[i].tipoCredito,tipoCredito);

                actualizar_binario(b,cantidadRegistrada); //funcion que carga el dat de nuevo luego de modificar el struct
                printf("MODIFICACI%cN REALIZADA CORRECTAMENTE!\n",162);
                printf("Orden\t  Nombre  Apellido\t  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
                printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[orden].orden,b[orden].nombre,b[orden].apellido,b[orden].importe,b[orden].tipoCredito,b[orden].dia,b[orden].mes,b[orden].anio,b[orden].nroCuotas,b[orden].importeCuota,b[orden].iva,b[orden].total,b[orden].activo);
                return 0;

            }
        }
    }
    printf("\nNO SE ENCUENTRA EL CLIENTE EN LA BASE DE DATOS!\n");
}

//FUNCIONES DE BUSQUEDA
//PUNTO 9//
int busqueda_numero_orden(struct Binario b[], int filas) //busca el cliente por ID
{
    int id;

    printf("Ingrese el ID del cliente que desea buscar:\n->");
    scanf("%d",&id);
    fflush(stdin);
    validar_opcion(&id,1,99999);//valido que el numero de orden sea un numero y no un caracter

    //recorro mi array de structs para ver si existe el cliente
    for(int pos=1; pos<filas; pos++)
    {
        if (id==b[pos].orden)
        {
            //si existe lo imprimo
            printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
            printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[pos].orden,b[pos].nombre,b[pos].apellido,b[pos].importe,b[pos].tipoCredito,b[pos].dia,b[pos].mes,b[pos].anio,b[pos].nroCuotas,b[pos].importeCuota,b[pos].iva,b[pos].total,b[pos].activo);
            return 1;
        }

    }

    printf("No se encontró al usuario con ese ID\n");
    return 0;

}


int busqueda_apellido(struct Binario b[], int filas)//funcion que le pide al usuario un apellido y si lo encuentra lo imprime
{
    char apellido[100];

    printf("Ingrese el apellido del cliente que desea buscar:\n->");
    gets(apellido);
    fflush(stdin);
    validar_texto(apellido);//valido que no contenga numeros

    //lo paso a mayuscula para poder comparar
    capitalizar(apellido);

    //recorro el array de structs en busqueda de coincidencia
    for (int pos=1; pos <filas; pos++)
    {
        if(strcmp(apellido,b[pos].apellido)==0)
        {
            printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
            printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b[pos].orden,b[pos].nombre,b[pos].apellido,b[pos].importe,b[pos].tipoCredito,b[pos].dia,b[pos].mes,b[pos].anio,b[pos].nroCuotas,b[pos].importeCuota,b[pos].iva,b[pos].total,b[pos].activo);
            return 1;
        }

    }

    printf("No se encontró al usuario con ese apellido\n");
    return 0;
}



//FUNCIONES BAJA
//PUNTO 11//
void baja_logica(struct Binario b, char nombreArchivo[]) //funcion que me permite dar de baja a un cliente (hace tambien la baja fisica automaticamente)
{
    int id,nRegistros;
    char r;
    FILE* archivo;


    archivo=fopen("creditos.dat","r+b");

    printf("Ingrese el numero del ID del cliente que desea dar de baja:\n->");
    scanf("%d",&id);
    fflush(stdin);
    validar_opcion(&id,1,99999); //valido que no sea un caracter

    fseek(archivo,0,SEEK_END); //posiciono el puntero al principio del archivo por las dudas
    nRegistros = ftell(archivo)/sizeof(struct Binario); //caculo el numero de renglones del archivo

    fseek(archivo,0,SEEK_SET);//vuelvo a setear el handler al principio del archivo
    fseek(archivo,(id-1)*sizeof(struct Binario),SEEK_SET);//busco con acceso directo (ahora si me salió)
    fread(&b,sizeof(struct Binario),1,archivo); //lo almaceno
    if(id==b.orden)//me fijo si es correcto el id del cliente del renglon con el que me habia pedido el usuario
    {
        printf("DATOS DEL CLIENTE SELECCIONADO:\n");
        printf("Orden\t  Nombre  Apellido\t  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n",164);
        printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t%d\n",b.orden,b.nombre,b.apellido,b.importe,b.tipoCredito,b.dia,b.mes,b.anio,b.nroCuotas,b.importeCuota,b.iva,b.total,b.activo);
        printf("\nDesea darlo de baja? [y/n]\n");
        scanf("%c",&r);
        fflush(stdin);

        if ((r=='y')||(r=='Y'))
        {
            baja_fisica(b,archivo,nombreArchivo); //hago tambien la baja fisica
            printf("Operacion realizada correctamente!\n");
        }

    }
    else
        printf("El cliente ingresado no se encuentra ne la base de datos.\n");

    fclose(archivo);

}



//PUNTO 12//
void baja_fisica(struct Binario b,FILE* binario, char str[])//funcion que guarda los datos de un cliente inactivo en un .xyz
{
    char dia[10];
    char mes[10];
    char anio[10];
    strcpy(str,"clientes_bajas_");


    //genero el nombre del archivo
    tiempoAhora_string(dia,mes,anio); //obtengo el tiempo actual de la pc
    strcat(dia,"-");
    strcat(dia,mes);
    strcat(dia,"-");
    strcat(dia,anio);
    strcat(dia,".xyz");
    //genero el string con el nombre del archvio entero
    strcat(str,dia);


    FILE* texto;
    //como se puede abrir el archivo mas de una vez al dia usamos append
    texto = fopen(str,"a");
    if ((texto==NULL))
    {
        errores(1);
    }

    //imrpimo al cliente en el .xyz y seteo todos los campos a 0
    b.activo=0;
    fprintf(texto,"%d,%s,%s,%.2f,%s,%d,%s,%d,%d,%.2f,%.2f,%.2f,%d\n",b.orden,b.nombre,b.apellido,b.importe,b.tipoCredito,b.dia,b.mes,b.anio,b.nroCuotas,b.importeCuota,b.iva,b.total,b.activo);
    b.orden=0;
    b.anio=0;
    strcpy(b.apellido,"");
    b.dia=0;
    b.importe=0;
    b.importeCuota=0;
    b.iva=0;
    strcpy(b.mes,"");
    strcpy(b.nombre,"");
    b.nroCuotas=0;
    b.total=0;
    strcpy(b.tipoCredito,"");

    //posiciono el puntero para reescribir el registro con todos los datos en 0
    fseek(binario,-sizeof(struct Binario),SEEK_CUR);
    fwrite(&b,sizeof(struct Binario),1,binario);


    fclose(texto);
}

//PUNTO 13//
int listar_xyz(struct Binario b, char nombreArchivo[]) //Recorro el csv modificado y guardo los datos de los clientes en un array de structs
{

    FILE *archivo; //puntero de mi archivo
    int leido=13; //variable para verificar que el scnaf este leyendo bien
    int i=0; //contador de ciclos


    //abro el archivo
    archivo=fopen(nombreArchivo,"r");


    //verifico que se este abriendo el archivo
    if (archivo==NULL)
    {
        errores(1);
    }

    //parseo e imprimo el archivo
    printf("Orden\t  Nombre  Apellido  Importe   Tipo de Credito \t dia mes a%co\tNro.Cuotas  Importe Cuotas\tIVA\tTotal Cuota  Activo\n\n",164);
    do
        {
            leido = fscanf(archivo,"%d,%249[^,],%249[^,],%f,%249[^,],%d,%249[^,],%d,%d,%f,%f,%f,%d\n",&b.orden,b.nombre,b.apellido,&b.importe,b.tipoCredito,&b.dia,&b.mes,&b.anio,&b.nroCuotas,&b.importeCuota,&b.iva,&b.total,&b.activo);

            if(leido!=13) //de esta forma evito que se repita el ultimo renglón (esta feo, tengo que cambiarlo)
                break;

            printf("%3d| %10s %10s %8.2lf  %14s \t %02d %3s %4d \t \t%d\t  %8.2lf  %8.2lf     %8.2lf \t %d\n",b.orden,b.nombre,b.apellido,b.importe,b.tipoCredito,b.dia,b.mes,b.anio,b.nroCuotas,b.importeCuota,b.iva,b.total,b.activo);

        }while(leido==13);

    fclose(archivo);

    return i;

}
