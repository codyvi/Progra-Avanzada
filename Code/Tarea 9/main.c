//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 11/03/2020
//Convierte numeros binarios y hexa a decimal, también un entero le pone precisión

#include "stdio.h"
#include "stdlib.h"

int asciiBinaryToInt(char *cBin)
{
    char cFinal = '\0';
    int iConvertido = 0;

    while(cFinal != *cBin)
    {
        iConvertido *= 2;
        if(*cBin++ == '1')
        {
            iConvertido += 1;
        }
    }
    return iConvertido;
}



int main()
{

    char cString[256];
    printf("%s", "Dame un numero en Binario: ");
    scanf("%s", cString);
    int iBinarioAInt = asciiBinaryToInt(cString);
    printf("%i \n", iBinarioAInt);




    return 0;
}
