//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Cambiar letras por valores númericos con pointers


#include <stdio.h>
//Funcion usada para cambiar los valores

void swap(char cWord[])
{
    char stop = '\0';
    while(*cWord != stop)
    {

        if(*cWord == 'o')
        {
            *cWord = '0';
        }

        else if(*cWord == 'i')
        {
            *cWord = '1';
        }

        else if(*cWord == 'u')
        {
            *cWord = '2';
        }
        
        else if(*cWord == 'e')
        {
            *cWord = '3';
        }

        else if(*cWord == 'a')
        {
            *cWord = '4';
        }

        cWord++;
    }
}

//Funcion principal
int main()
{

    char cWord[256];
    printf("%s \n", "Dame una palabra: ");
    scanf("%s", cWord);
    swap(cWord);
    printf("La palabra cambiada es: %s \n", cWord);

    return 0;
}