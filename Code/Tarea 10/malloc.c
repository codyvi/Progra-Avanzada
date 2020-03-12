//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 11/03/2020
//Convierte numeros binarios y hexa a decimal, también un entero le pone precisión

#include "stdio.h"
#include "stdlib.h"

//función para string largo
void extremlyLargeString(char *pStr, int iLen_max, int iCurrent_size){
    if(pStr != NULL){
        int c = EOF;
        int i = 0;
        while((c = getchar()) != '\n' && c != EOF){
            pStr[i++] = (char)c;

            if(i == iCurrent_size){
                iCurrent_size = i + iLen_max;
                pStr = realloc(pStr, iCurrent_size);
            }
        }
        pStr[i] = '\0';
    }
}

//función principal
int main()
{
    int maxLen = 10;
    int iTam = 0;

    char *pStr = malloc(maxLen);
    iTam = maxLen;

    printf("\n Introduce un string largo: ");

    extremlyLargeString(pStr, maxLen, iTam);
    printf("\n Valor del string largo: %s \n\n",pStr);
    free(pStr);
    return 0;
}
