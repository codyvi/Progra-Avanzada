//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 11/03/2020
//Pregunta al usuario un entero, un char y un double e imprime el tamaño en bits

#include "stdio.h"
#include "float.h"
#include "string.h"

union Valores
{
    int i;
    double d;
    char str[100];
};


//función principal del programa
int main()
{

    union Valores datos;

    printf("Enter a int number: ");
    scanf("%d", &datos.i);
    printf("Your integer %d storage size is %d bytes.\n", datos.i, sizeof(datos.i));

    return 0;
}