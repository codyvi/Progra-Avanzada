//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 19/03/2020
//Convierte numeros hexadecimales, binarios, base 8 y dividir ente 2 y multiplicar por 2

#include <stdio.h>
#include <stdlib.h>

//Función para convertir strings Hexadecimales a int
int asciiHEXToInt(char *cHex)
{
    char cFinal = '\0';
    int iConvertido = 0;
    int i = 0;
    while(cFinal != *cHex && i < 8)
    {
        iConvertido *= 16;
        if(*cHex <= '9' && *cHex >= '0') 
        {
            iConvertido += *cHex - '0';
        }

        else if(*cHex == 'A' || *cHex == 'a') 
        {
            iConvertido+=10;
        }

        else if(*cHex == 'B' || *cHex == 'b') 
        {
            iConvertido+=11;
        }

        else if(*cHex == 'C' || *cHex == 'c') 
        {
            iConvertido+=12;
        }

        else if(*cHex == 'D' || *cHex == 'd') 
        {
            iConvertido+=13;
        }

        else if(*cHex == 'E' || *cHex == 'e') 
        {
            iConvertido+=14;
        }
        
        else if(*cHex == 'F' || *cHex == 'f') 
        {
            iConvertido+=15;
        }

        else return iConvertido/16;

        cHex++;

        i++;
    }
    return iConvertido;
}

int asciiBinaryToInt(char *cBin)
{
    char cFinal = '\0';
    int iConvertido = 0;

    int i = 0;
    while(cFinal != *cBin && i < 8)
    {
        iConvertido *= 2;
        if(*cBin++ == '1')
        {
            iConvertido += 1;
        }

        else if(*cBin == '0')
        {

        }

        else
        {
            return iConvertido/2;
        }

        cBin++;
        i++;
        
    }
    return iConvertido;
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
