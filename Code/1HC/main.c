#include "stdlib.h"
#include "time.h"
#include "stdio.h"

long randManual(long MySeed)
{
    long number = MySeed * 25214903917 + 11;
    return number % 100;
}

int main()
{
    clock_t Seed = clock();

    printf("Los numeros randoms son: \n");
    for(int i = 0; i < 10; i++)
    {
        printf("%lo \n", randManual(Seed));
        Seed = randManual(Seed);
    }

    return 0;
}