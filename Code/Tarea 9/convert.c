//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 11/03/2020
//Convierte numeros binarios y hexa a decimal, también un entero le pone precisión

#include "stdio.h"
#include "stdlib.h"


int main()
{

    char cString[256];
    printf("%s", "Dame un numero en Binario: ");
    scanf("%s", cString);
    int iBinarioAInt = asciiBinaryToInt(cString);
    printf("%i \n", iBinarioAInt);




    return 0;
}
