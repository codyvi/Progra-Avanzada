//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Pide al usuario datos de su agente y los guarada en una estructura

#include "stdio.h"
#include "string.h"

//Estructura usada para guardar los datos
struct Agent{
    char cNombre[30];
    char cUNombre[30];
    int iEdad;
    char cGenero[12];
    char cMision[25];
};

int main()
{
    struct Agent P;
    char buf[10]; //Variable temporal
    printf("%s\n", "Introduce el nombre del agente: ");
    fgets(P.cNombre,30,stdin);

    printf("%s\n", "Introduce el apellido del agente: ");
    fgets(P.cUNombre,30,stdin);

    printf("%s\n", "Introduce la edad del agente: ");
    fgets(buf,10,stdin);

    printf("%s\n", "Introduce el genero del agente: ");
    fgets(P.cGenero,12,stdin);

    printf("%s\n", "Introduce el id de la mision: ");
    fgets(P.cMision,25,stdin);

    P.iEdad = atoi(buf); //Convirtiendo String a Int
    //Imprimiendo al Agente
    printf("%s\n", "Agente: ");
    printf("%s", P.cNombre);
    printf("%s", P.cUNombre);
    printf("%i\n", P.iEdad);
    printf("%s", P.cGenero);
    printf("%s", P.cMision);

}
