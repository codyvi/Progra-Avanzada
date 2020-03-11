#include <stdio.h>
#include <stdlib.h>


int asciiBinaryToInt(char *cString){
    char cEnd = '\0';
    int iResult = 0;

    while(*cString != cEnd){
        iResult *= 2;
        if(*cString++ == '1'){
            iResult+=1;
        }
    }
    return iResult;
}

int asciiHEXToInt(char *cString){
    char cEnd = '\0';
    int iResult = 0;
    
    while(*cString != cEnd){
        iResult *= 16;
        if(*cString <= '9' && *cString >= '0') iResult += *cString - '0';
        if(*cString == 'A') iResult+=10;
        if(*cString == 'B') iResult+=11;
        if(*cString == 'C') iResult+=12;
        if(*cString == 'D') iResult+=13;
        if(*cString == 'E') iResult+=14;
        if(*cString == 'F') iResult+=15;
        cString++;
    }
    return iResult;
}

double asciiToDouble(char *s){
    return strtod(s, NULL);
}

int main(){
    char cString[256];
    printf("%s \n", "Introduce un numero en binario: ");
    scanf("%s", cString);
    int iBtI = asciiBinaryToInt(cString);
    printf("%i \n", iBtI);

    printf("%s \n", "Introduce un numero en hex: ");
    scanf("%s", cString);
    int iHtI = asciiHEXToInt(cString);
    printf("%i \n", iHtI);

    printf("%s \n", "Introduce un numero: ");
    scanf("%s", cString);
    double iAtI = asciiToDouble(cString);
    printf("%f \n", iAtI);
}
