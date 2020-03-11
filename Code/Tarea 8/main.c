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
    char str[101];
};


//función principal del programa
int main()
{

    union Valores datos;

    printf("Enter a int number: ");
    scanf("%d", &datos.i);
    printf("Your integer %d storage size is %d bytes.\n", datos.i, sizeof(datos.i));

    printf("Enter a double: ");
    scanf("%lf", &datos.d);
    printf("Your double %lf storage size is %d bytes, I can read any number from %lf to %lf in this data type \n", 
    datos.d, (int)sizeof(datos.d), DBL_MIN, DBL_MAX);
    
    printf("Enter a string: ");
    scanf("%100s", &datos.str);
    printf("Your string %s storage size is %d bytes.\n", datos.str, sizeof(datos.str));

  
    return 0;
}