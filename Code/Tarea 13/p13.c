#include "asciitrans.h"
int main(){

    char cString[256];
    printf("%s", "Dame un numero en Binario: ");
    scanf("%s", cString);
    int iBinarioAInt = asciiBinaryToInt(cString);
    printf("%i \n", iBinarioAInt);

    printf("%s", "Dame un numero en Hexadecimal: ");
    scanf("%s", cString);
    int iHexAInt = asciiHEXToInt(cString);
    printf("%i \n", iHexAInt);

    printf("%s", "Dame un numero: ");
    scanf("%s", cString);
    double dStringToDouble = asciiToDouble(cString);
    printf("%f", dStringToDouble);

    return 0;
}