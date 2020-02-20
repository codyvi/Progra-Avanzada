//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Cambiar letras por valores númericos con pointers


#include <stdio.h>

void changer(char cString[]){
    char cEnd = '\0';
    while(*cString != cEnd){
        if(*cString == 'a')
            *cString = '4';
        else if(*cString == 'e')
            *cString = '3';
        else if(*cString == 'i')
            *cString = '1';
        else if(*cString == 'o')
            *cString = '0';
        else if(*cString == 'u')
            *cString = '2';
            
        cString++;
    }
}

int main(){
    char cString[256];
    printf("%s \n", "Introduce una palabra: ");
    scanf("%s", cString);
    changer(cString);
    printf("%s \n", cString);
}