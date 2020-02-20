//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Implementación de Fibonacci recursivo y factorial

#include "stdio.h"

//Función recursiva para 
long int Fact(int iNumber)
{
    if(iNumber>=1)
    {
        return iNumber*Fact(iNumber-1);
    }

    else
    {
        return 1;
    }
    
}

//Función Recursiva para caluclar Fibonacci
int fibo(int iNumber, int first, int second)
{
    printf("%d ", first);

    if(iNumber == 0)
    {
        return first;
    }

    if(iNumber == 1)
    {
        return second;
    }

    
    return fibo(iNumber-1, second, first +second);

    
}

int main()
{

    int iNumber;
    printf("Dame un numero para obtener el factorial y Fibonacci: ");
    scanf("%d", &iNumber);
    long int iNumberFac = Fact(iNumber);
    printf("Los primeros %d elementos de fibo son: ", iNumber);
    fibo(iNumber,0,1);
    printf("\nEl factorial de %d es %ld \n",iNumber,iNumberFac);
    return 0;
}