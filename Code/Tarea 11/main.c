#include <stdio.h>
#include <stdlib.h>

int asciiHEXToInt(char *cString){
    char cEnd = '\0';
    int iResult = 0;
    int i = 0;
    while(*cString != cEnd && i < 8){
        iResult *= 16;
        if(*cString <= '9' && *cString >= '0') iResult += *cString - '0';
        else if(*cString == 'A' || *cString == 'a') iResult+=10;
        else if(*cString == 'B' || *cString == 'b') iResult+=11;
        else if(*cString == 'C' || *cString == 'c') iResult+=12;
        else if(*cString == 'D' || *cString == 'd') iResult+=13;
        else if(*cString == 'E' || *cString == 'e') iResult+=14;
        else if(*cString == 'F' || *cString == 'f') iResult+=15;
        else return iResult/16;
        cString++;
        i++;
    }
    return iResult;
}

int asciiBinaryToInt(char *cString){
    char cEnd = '\0';
    int iResult = 0;

    int i = 0;
    while(*cString != cEnd && i < 8){
        iResult *= 2;
        if(*cString == '1'){
            iResult+=1;
        } else if(*cString == '0'){
        } else {
            return iResult/2;
        }
        cString++;
        i++;
    }
    return iResult;
}

int asciiOCTToInt(char *cString){
    char cEnd = '\0';
    int iResult = 0;

    int i = 0;
    while(*cString != cEnd && i < 8){
        iResult *= 8;
        if(*cString <= '7' && *cString >= '0') iResult += *cString - '0';
        else return iResult/8;
        cString++;
        i++;
    }
    return iResult;
}

int divideByTwo(int *i){
    return *i >> 1;
}

int multByTwo(int *i){
    return *i << 1;
}

int main(){
    char cString[256];
    int iNumber = 0;
    
    while(1 == 1){
        int option = -1;
        printf("%s \n", "1. Binario a decimal: ");
        printf("%s \n", "2. Hexadecimal a decimal: ");
        printf("%s \n", "3. Octal a decimal: ");
        printf("%s \n", "4. Multiplicar por dos un decimal: ");
        printf("%s \n", "5. Dividir por dos un decimal: ");
        scanf("%d", &option);
        switch (option){
            case 1:
                printf("%s \n", "Introduce un numero en binario: ");
                scanf("%s", cString);
                int iBtI = asciiBinaryToInt(cString);
                printf("%i \n", iBtI);
                break;

            case 2:
                printf("%s \n", "Introduce un numero en hex: ");
                scanf("%s", cString);
                int iHtI = asciiHEXToInt(cString);
                printf("%i \n", iHtI);
                break;

            case 3:
                printf("%s \n", "Introduce un numero en base 8: ");
                scanf("%s", cString);
                int iEtI = asciiOCTToInt(cString);
                printf("%i \n", iEtI);
                break;

            case 4:
                printf("%s \n", "Introduce un numero para multiplicar por 2: ");
                scanf("%i", &iNumber);
                int iMb2 = multByTwo(&iNumber);
                printf("%i \n", iMb2);
                break;

            case 5:
                printf("%s \n", "Introduce un numero para dividir entre 2: ");
                scanf("%i", &iNumber);
                int iDb2 = divideByTwo(&iNumber);
                printf("%i \n", iDb2);
                break;
            default:
                break;
        }
        printf("%s","\n");
    }
}
