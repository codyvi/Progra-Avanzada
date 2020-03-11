
#include <stdio.h>
#include <string.h>

struct Agente{
    char cName[30];
    char cLastName[30];
    int iAge;
    char cGender[12];
    char cMission[25];
};

union Data{
    int iInt;
    double dDouble;
    char cString[80];
    struct Agente *A;
};

void printAgent(union Data D){
    printf("%s\n", "Agente: ");
    printf("%s\n", D.A->cName);
    printf("%s\n", D.A->cLastName);
    printf("%i\n", D.A->iAge);
    printf("%s\n", D.A->cGender);
    printf("%s\n", D.A->cMission);
}

int main(int argc, const char* argv[]){
    union Data D;
    printf("%s\n", "Introduce el nombre del agente: ");
    scanf("%s", D.A->cName);

    printf("%s\n", "Introduce el apellido del agente: ");
    scanf("%s", D.A->cLastName);

    printf("%s\n", "Introduce la edad del agente: ");
    scanf("%i", &D.A->iAge);

    printf("%s\n", "Introduce el genero del agente: ");
    scanf("%s", D.A->cGender);

    printf("%s\n", "Introduce el id de la mision: ");
    scanf("%s", D.A->cMission);

    printAgent(D);
}