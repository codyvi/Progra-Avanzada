//
//  main.c
//  practica13
//
//  Created by Pepe Hdez hdez on 22/04/20.
//  Copyright © 2020 itesm. All rights reserved.
//

#include <stdio.h>
#include "asciitrans.h"

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
