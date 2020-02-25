//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Menu donde se guardan los datos de los agentes, se pueden desplegar, agregar o borrar.

#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"

//struct usada para guardar los datos del agente
struct Agent{
    char cNombre[30];
    char cUNombre[30];
    int iEdad;
    char cGenero[12];
    char cMision[12][12];
    char cActivos[13][13];
};
//Struct usada para acceder a los datos del agente
struct Node{
    int data;
    struct Node *next;
    struct Agent A;
};

//Variables Globales 
int counter = 0;
int counterActivos = 0;
int counterMisiones = 0;

//funcion principal
int main()
{
    int iInput;
    int iDAta;
    int iNumActivos;
    int iNumMisiones;

    for(;;)
    {
        struct Agente A;
        printf("\n-------------------------------------------\n");
        printf("1. Agregar a un nuevo agente \n");
        printf("2. Borrar un agente\n");
        printf("3. Mostrar a los agentes\n");
        scanf("%d", &iInput);
    }



    return 0;
}