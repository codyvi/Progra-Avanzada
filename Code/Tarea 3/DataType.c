//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Pregunta al usuario un entero, un char y un double e imprime el tamaño en bits

#include "stdio.h"
#include "float.h"


//Función Principal del programa
int main()
{
    //Variables a usar para programa
    int iNum;
    char cChar;
    double dNum;
    //Obtencion de entero, caracyer y double
    printf("Enter a int number: ");
    scanf("%d", &iNum);

    printf("Enter a char: ");
    scanf(" %c", &cChar);

    printf("Enter a double: ");
    scanf(" %lf", &dNum);
    //Impresión de los datos
    printf("Your integer %d storage size is %d bytes.\n", iNum, sizeof(iNum));
    printf("Your char %c storage size is %d bytes. And I can read it as %c or as %d.\n", 
    cChar, sizeof(cChar), cChar, cChar);
    printf("Your double %lf storage size is %d bytes, I can read any number from %lf to %lf in this data type \n", 
    dNum, (int)sizeof(dNum), DBL_MIN, DBL_MAX);

    return 0;
}