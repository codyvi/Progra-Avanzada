#include "Convert.h"
#include <stdio.h>

int main() {
    char temp[32];

    printf("Ingresa un numero binario: ");
    scanf("%s", temp);

    printf("Numero: %i\n", asciiBinaryToInt(temp));

    printf("Ingresa un numero hexadecimal: ");
    scanf(" %s", temp);

    printf("Numero: %i\n", asciiHEXToInt(temp));
    
    printf("Ingresa un numero decimal: ");
    scanf(" %s", temp);

    printf("Numero: %f\n", asciiToDouble(temp));
}