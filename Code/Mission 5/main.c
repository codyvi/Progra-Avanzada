//A00822455 David Alonso Cantú Martínez
//Programa para calcular pi
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int omp_get_thread_num();

//Funcion single thread
void single(time_t start, time_t stop){
    int iRec = 0;
    printf("Dame el numero de rectangulos\n");
    scanf("%d", &iRec);
    start = clock();

    double width = 1.0 / iRec;
    double x;
    double height;
    double area = 0.0;
    double pi;
    int i;

    for (i = 0; i < iRec; i++){
        x = i * width;
        height = sqrt(1.0 - x * x);
        area += width * height;
    }
    pi = 4.0 * (float)area;
    stop = clock();
    double time = 0.0;
    time += (double)(stop-start)/CLOCKS_PER_SEC;

    printf("PI = %10.15lf\n", pi);
    printf("Time: %f seconds", time);
 
    return;
}

//Función multithread
void multi(time_t start, time_t stop){
    int iRec = 0;

    printf("Dame el numero de rectangulos\n");
    scanf("%d", &iRec);
    start = clock();

    double width = 1.0 / iRec;
    double x;
    double height;
    double area = 0.0;
    double pi;
    int i;

    #pragma omp parallel
    {
      #pragma omp for private(x, i, height) reduction(+:area)
      for (i = 0; i < iRec; i++){
          x = i * width;
          height = sqrt(1.0 - x * x);
          area += width * height;
      }
      //printf("Thread rank: %d \n", omp_get_thread_num());
    }
    pi = 4.0 * area;
    stop = clock();
    double time = 0.0;
    time += (double)(stop-start)/CLOCKS_PER_SEC;

    printf("PI = %10.15lf\n", pi);
    printf("Time: %f seconds", time);
    return;
}

//Función principal
int main() {
    int option = 0;
    time_t start,stop;
    
    printf("1. Multi thread\n");
    printf("2. Single thread\n");
    scanf("%d", &option);
    
    if(option == 1)
        multi(start, stop);
    else if(option == 2)
        single(start, stop);
    else
        printf("Solo estan esas dos opciones\n");
    return 0;
}
