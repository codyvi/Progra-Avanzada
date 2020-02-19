//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Pregunta al usuario datos de una matriz 2x2 y desplegar
//las dos matrices, la suma, resta y multiplicación de cada una

#include "stdio.h"

void printMatrices(int iMatrixA[2][2]){
    printf("La matriz es: \n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d\t", iMatrixA[i][j]);   // Imprimir un renglon
        }
        printf("\n"); // Cambiar de renglon
    }
}



//Función Principal 
int main()
{
    //Varaibles a usar para matrices  
    int iMatOne[2][2];
    int iMatTwo[2][2];

    

    
    printf("Introduce los 4 elementos de la primera matriz: \n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            scanf("%d", &iMatOne[i][j]);
        }
    }

    printf("Introduce los 4 elementos de la segunda matriz: \n");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            scanf("%d", &iMatTwo[i][j]);
        }
    }

    printMatrices(iMatOne);
    printMatrices(iMatTwo);


    return 0;
}