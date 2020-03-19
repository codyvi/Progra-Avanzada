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

        else if(*cHex == 'A' || *cHex == 'a') 
        {
            iConvertido+=10;
        }

        else if(*cHex == 'B' || *cHex == 'b') 
        {
            iConvertido+=11;
        }

        else if(*cHex == 'C' || *cHex == 'c') 
        {
            iConvertido+=12;
        }

        else if(*cHex == 'D' || *cHex == 'd') 
        {
            iConvertido+=13;
        }

        else if(*cHex == 'E' || *cHex == 'e') 
        {
            iConvertido+=14;
        }
        
        else if(*cHex == 'F' || *cHex == 'f') 
        {
            iConvertido+=15;
        }

        cHex++;
    }
    return iConvertido;
}

//Función para convertir de string a double
double asciiToDouble(char *cNum)
{
    return strtod(cNum, NULL);
}

//función principal 
int main()
{

    char cString[256];
    printf("%s", "Dame un numero en Binario: ");
    scanf("%s", cString);
    int iBinarioAInt = asciiBinaryToInt(cString);
    printf("%i \n", iBinarioAInt);

    printf("%s", "Dame un numero en Hexadecimal: ");
    scanf("%s", cString);
    int iHexAInt = asciiHEXToInt(cString);
    printf("%i \n", iHexAInt);

    printf("%s", "Dame un numero: ");
    scanf("%s", cString);
    double dStringToDouble = asciiToDouble(cString);
    printf("%f", dStringToDouble);

    return 0;
}
