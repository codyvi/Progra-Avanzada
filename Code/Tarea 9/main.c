//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 11/03/2020
//Convierte numeros binarios y hexa a decimal, también un entero le pone precisión

#include "stdio.h"
#include "stdlib.h"

//función para convertir Binario a entero
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

//función para convertit hexadecimal a entero
int asciiHEXToInt(char *cHex)
{
    char cFinal = '\0';
    int iConvertido = 0;
    while(cFinal != *cHex)
    {
        iConvertido *= 16;
        if(*cHex <= '9' && *cHex >= '0') 
        {
            iConvertido += *cHex - '0';
        }

        if(*cHex == 'A') 
        {
            iConvertido+=10;
        }

        if(*cHex == 'B') 
        {
            iConvertido+=11;
        }

        if(*cHex == 'C') 
        {
            iConvertido+=12;
        }

        if(*cHex == 'D') 
        {
            iConvertido+=13;
        }

        if(*cHex == 'E') 
        {
            iConvertido+=14;
        }
        
        if(*cHex == 'F') 
        {
            iConvertido+=15;
        }

        cHex++;
    }
    return iConvertido;
}

//función principal 
int main()
{

    char cString[256];
    printf("%s", "Dame un numero en Binario: ");
    scanf("%s", cString);
    int iBinarioAInt = asciiBinaryToInt(cString);
    printf("%i \n", iBinarioAInt);

    printf("%s", "Introduce un numero en hex: ");
    scanf("%s", cString);
    int iHexAInt = asciiHEXToInt(cString);
    printf("%i \n", iHexAInt);




    return 0;
}
