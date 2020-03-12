//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 11/03/2020
//Convierte numeros binarios y hexa a decimal, también un entero le pone precisión

#include "stdio.h"
#include "stdlib.h"


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

int main(int argc, char *argv[]){
    char binary[32];
    if(argc>=2) { 
        printf("\n Numero de Argumentos dados: %d",argc); 
        printf("\n----Argumentos dados----"); 
        for(int i=1;i<argc;i++) 
            printf("\nargv[%d]: %d",i, asciiHEXToInt(argv[i])); 
    } 
    return 0;
}
