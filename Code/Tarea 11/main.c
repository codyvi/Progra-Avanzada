//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 19/03/2020
//Convierte numeros hexadecimales, binarios, base 8 y dividir ente 2 y multiplicar por 2
#include "stdio.h"
#include "stdlib.h"

//Función para convertir strings Hexadecimales a entero
int asciiHEXToInt(char *cHex)
{
    char cFinal = '\0';
    int iConvertido = 0;
    int i = 0;
    while(cFinal != *cHex && i < 8)
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

        else return iConvertido/16;

        cHex++;

        i++;
    }
    return iConvertido;
}

//función para convertir Binario a entero
int asciiBinaryToInt(char *cBin)
{
    char cFinal = '\0';
    int iConvertido = 0;

    int i = 0;
    while(cFinal != *cBin && i < 8)
    {
        iConvertido *= 2;
        if(*cBin++ == '1')
        {
            iConvertido += 1;
        }
        i++;
        
    }
    return iConvertido;
}

//Función que convierte base 8 a int
int asciiOCTToInt(char *cOct)
{
    char cEnd = '\0';
    int iConvertido = 0;

    int i = 0;
    while(*cOct != cEnd && i < 8)
    {
        iConvertido *= 8;
        if(*cOct <= '7' && *cOct >= '0') 
        {
            iConvertido += *cOct - '0';
        }
        else  return iConvertido/8;
        cOct++;
        i++;
    }
    return iConvertido;
}

//Divide entre 2 con bit operations
int divideByTwo(int *i)
{
    return *i >> 1;
}

//Multiplica por 2 con bit operations
int multByTwo(int *i)
{
    return *i << 1;
}

int main()
{
    char cString[256];
    int iNumber = 0;

    printf("%s", "Dame un numero en Hexadecimal: ");
    scanf("%s", cString);
    int iHexAInt = asciiHEXToInt(cString);
    printf("%i \n", iHexAInt);
    
    printf("%s", "Dame un numero en Binario: ");
    scanf("%s", cString);
    int iBinarioAInt = asciiBinaryToInt(cString);
    printf("%i \n", iBinarioAInt);

    printf("%s", "Introduce un numero en base 8: ");
    scanf("%s", cString);
    int iEtI = asciiOCTToInt(cString);
    printf("%i \n", iEtI);
  
    printf("%s", "Introduce un numero para multiplicar por 2: ");

    scanf("%i", &iNumber);
    int iMb2 = multByTwo(&iNumber);
    printf("%i \n", iMb2);
    
    printf("%s", "Introduce un numero para dividir entre 2: ");
    scanf("%i", &iNumber);
    int iDb2 = divideByTwo(&iNumber);
    printf("%i \n", iDb2);

    return 0;
}
