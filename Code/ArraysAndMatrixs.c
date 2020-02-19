//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Pregunta al usuario datos de una matriz 2x2 y desplegar
//las dos matrices, la suma, resta y multiplicación de cada una

#include "stdio.h"
#define size 2

//Imprime las matrices
void printMat(int iMat[size][size]){
    printf("La matriz es: \n");
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            //Imprime cada valor de la matriz 
            printf("%d\t", iMat[i][j]);   
        }
        //Cambia de renglón
        printf("\n"); 
    }
}

//Suma dos matrices y luego despliega el resultado
void SumaMat(int iMatA[size][size], int iMatB[size][size])
{
    int iMatAux[size][size];
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            iMatAux[i][j] = iMatA[i][j] + iMatB[i][j]; //Suma las matrices
        }
    }
    printf("---Suma de dos matrices---\n");
    printMat(iMatAux); //Llama a printMat para desplegar el resultado

}

//Resta dos matrices y luego despliega el resultado
void RestaMat(int iMatA[size][size], int iMatB[size][size])
{
    int iMatAux[size][size];
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            iMatAux[i][j] = iMatA[i][j] - iMatB[i][j]; //Resta las matrices
        }
    }
    printf("---Resta de dos matrices---\n"); 
    printMat(iMatAux); //Llama a printMat para desplegar el resultado
}

//Multiplica dos matrices, y luego despliega el resultado
void MultMat(int iMatA[size][size], int iMatB[size][size])
{
    int iMatAux[size][size];
    int iAux = 0;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            for(int k = 0; k < size; k++)
            {
                iAux +=  iMatA[i][k]*iMatB[k][j]; //Multiplicando las matrices
            }
            iMatAux[i][j] = iAux; //Asignando valor aux a la matriz a desplegar
            iAux = 0;
        }
    }
    printf("---Multiplicacion de dos matrices---\n"); 
    printMat(iMatAux); //Llama a printMat para desplegar el resultado
}

//Función Principal
int main()
{
    //Varaibles a usar para matrices  
    int iMatOne[size][size];
    int iMatTwo[size][size];

    
    printf("Dame los 4 elementos de la matriz uno: \n");
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            scanf("%d", &iMatOne[i][j]);
        }
    }

    printf("Dame los 4 elementos de la matriz dos: \n");
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            scanf("%d", &iMatTwo[i][j]);
        }
    }
    
    //Llamada a funciones 
    printf("---Matriz Uno---\n");
    printMat(iMatOne);
    printf("---Matriz Dos---\n");
    printMat(iMatTwo);
    SumaMat(iMatOne, iMatTwo); 
    RestaMat(iMatOne, iMatTwo);
    MultMat(iMatOne, iMatTwo);


    return 0;
}