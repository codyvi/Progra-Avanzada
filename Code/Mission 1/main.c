#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct Agente{
    char cName[30];
    char cLastName[30];
    int iAge;
    char cGender[12];
    char cMission[12][12];
    char cActivos[13][13];
};

struct Node{
    int data;
    struct Node *next;
    struct Agente A;
};

struct Node *head = NULL;
void insert(struct Agente);
void traverse();
void delete(int);
void search(char[30]);
void searchPorActivo(char [30]);
int misionesVal(char[12]);
int activosVal(char[13]);
int counter = 0;
int counterActivos = 0;
int counterMisiones = 0;

int main(){
    int input, data, numActivos, numMisiones;
    char cActivoOrApellido[20] = "";
    int llave = 4;
    int intento;
    printf("Introduzca la llave:\n \n");
    printf("(Llave %d )\n", llave);
    scanf("%d", &intento);

    if(intento == llave){
        printf("Llave correcta");
        llave = 0;
    } else {
        printf("Llave incorrecta");
        llave = 4;
    }
    for(;;){
        struct Agente A;
        printf("\n-------------------------------------------\n");
        printf("1. Introducir un nuevo Agente.\n \n");
        printf("2. Imprimir los agentes.\n \n");
        printf("3. Borrar un agente.\n \n");
        printf("4. Buscar un agente por apellido.\n \n");
        printf("5. Buscar un agente por activo.\n \n");
        scanf("%d", &input);
        if  (input == 1) {
            printf("Ingresa el nombre del agente: ");
            scanf("%s", A.cName);
            printf("Ingresa el apellido del agente: ");
            scanf("%s", A.cLastName);
            printf("Ingresa la edad del agente: ");
            scanf("%d", &A.iAge);
            // scanf("%d", &data);

            printf("Ingresa cuantos activos tiene el agente\n");
            scanf("%d", &numActivos);
            while(numActivos > 0){
                char cActivos[13] = "";
                printf("Ingresa al activo\n");
                scanf("%s", cActivos);
                if(activosVal(cActivos)){
                    strcpy(A.cActivos[counterActivos], cActivos);
                    counterActivos++;
                    printf("Agente añadida de manera exitosa \n");
                    numActivos--;
                } else {
                    printf("Agente no cumple con el formato\n");
                }
            }

            printf("Ingresa cuantas misiones tiene el agente\n");
            scanf("%d", &numMisiones);
            while(numMisiones > 0){
                char cMission[12] = "";
                printf("Ingresa la siguiente mision\n");
                scanf("%s", cMission);
                if(misionesVal(cMission)){
                    strcpy(A.cMission[counterMisiones], cMission);
                    counterMisiones++;
                    printf("Mision añadida de manera exitosa \n");
                    numMisiones--;
                } else {
                    printf("Mision no cumple con el formato\n");
                }
            }
            insert(A);
        }
        else if (input == 2) {
            traverse();
        }
        else if (input == 3) {
            traverse();
            if(head != NULL){
                printf("Introduce el ID del elemento a borrar: \n");
                scanf("%d", &data);
                delete(data);
            }
        }

        else if (input == 4){
            traverse();
            if(head != NULL){
                printf("Introduce el apellido del agente a buscar: \n");
                scanf("%s", cActivoOrApellido);
                search(cActivoOrApellido);
            }
        }
        else if (input == 5){
            traverse();
            if(head != NULL){
                printf("Introduce el activo del agente a buscar: \n");
                scanf("%s", cActivoOrApellido);
                searchPorActivo(cActivoOrApellido);
            }
        }
        printf("\n-------------------------------------------\n");
    }
}

void searchPorActivo(char cActivo[30]){
    struct Node *temp;
    temp = head;

    char nuevoApellido[30] = "";
    int numActivos, numMisiones;
    while(temp != NULL){
        for(int i = 0; i < counterActivos; i++){
            if(!strcmp(temp->A.cActivos[i], cActivo)){
                printf("Encontrado \n");
                int opcion, opcion2;
                printf("Quieres Editar al agente? (1)\n");
                printf("Quieres Borrar al agente? (2)\n");
                scanf("%i", &opcion);
                if(opcion == 1){
                    printf("Quieres Editar los activos? (1)\n");
                    printf("Quieres Editar las misiones? (2)\n");
                    scanf("%i", &opcion2);
                    if(opcion2 == 1){
                        printf("Ingresa cuantos activos agregar\n");
                        scanf("%d", &numActivos);
                        while(numActivos > 0){
                            char cActivos[13] = "";
                            printf("Ingresa al activo\n");
                            scanf("%s", cActivos);
                            if(activosVal(cActivos)){
                                strcpy(temp->A.cActivos[counterActivos], cActivos);
                                counterActivos++;
                                printf("Agente añadida de manera exitosa \n");
                                numActivos--;
                            } else {
                                printf("Agente no cumple con el formato\n");
                            }
                        }
                    }
                    if(opcion2 == 2){
                        printf("Ingresa cuantas misiones tiene el agente\n");
                        scanf("%d", &numMisiones);
                        while(numMisiones > 0){
                            char cMission[12] = "";
                            printf("Ingresa la siguiente mision\n");
                            scanf("%s", cMission);
                            if(misionesVal(cMission)){
                                strcpy(temp->A.cMission[counterMisiones], cMission);
                                counterMisiones++;
                                printf("Mision añadida de manera exitosa \n");
                                numMisiones--;
                            } else {
                                printf("Mision no cumple con el formato\n");
                            }
                        }
                    }
                }
                if (opcion == 2){
                    delete(temp->data);
                }
                traverse();
                break;
            } else {
                printf("No encontrado \n");
            }
        }
        temp = temp->next; 
    }

}

void search(char cApellido[30]){
    struct Node *temp;
    temp = head;

    char nuevoApellido[30] = "";
    int numActivos, numMisiones;
    while(temp != NULL){
        if(!strcmp(temp->A.cLastName, cApellido)){
            printf("Encontrado \n");
            int opcion, opcion2;
            printf("Quieres Editar al agente? (1)\n");
            printf("Quieres Borrar al agente? (2)\n");
            scanf("%i", &opcion);
            if(opcion == 1){
                printf("Quieres Editar los activos? (1)\n");
                printf("Quieres Editar las misiones? (2)\n");
                scanf("%i", &opcion2);
                if(opcion2 == 1){
                    printf("Ingresa cuantos activos agregar\n");
                    scanf("%d", &numActivos);
                    while(numActivos > 0){
                        char cActivos[13] = "";
                        printf("Ingresa al activo\n");
                        scanf("%s", cActivos);
                        if(activosVal(cActivos)){
                            strcpy(temp->A.cActivos[counterActivos], cActivos);
                            counterActivos++;
                            printf("Agente añadida de manera exitosa \n");
                            numActivos--;
                        } else {
                            printf("Agente no cumple con el formato\n");
                        }
                    }
                }
                if(opcion2 == 2){
                    printf("Ingresa cuantas misiones tiene el agente\n");
                    scanf("%d", &numMisiones);
                    while(numMisiones > 0){
                        char cMission[12] = "";
                        printf("Ingresa la siguiente mision\n");
                        scanf("%s", cMission);
                        if(misionesVal(cMission)){
                            strcpy(temp->A.cMission[counterMisiones], cMission);
                            counterMisiones++;
                            printf("Mision añadida de manera exitosa \n");
                            numMisiones--;
                        } else {
                            printf("Mision no cumple con el formato\n");
                        }
                    }
                }
            }
            if (opcion == 2){
                delete(temp->data);
            }
            traverse();
            break;
        } else {
            printf("No encontrado \n");
        }
        temp = temp->next; 
    }

}

int misionesVal(char mision[12]){
    int i = 0;
    for(; i < 3; i++){
        if(!isdigit(mision[i]))
            return 0;
    }
    for(; i < 12; i++){
        if(!isalpha(mision[i]))
            return 0;
    }
    return 1;
}

int activosVal(char agente[13]){
    int i = 0;
    for(; i < 4; i++){
        if(!isdigit(agente[i]))
            return 0;
    }
    for(; i < 13; i++){
        if(!isalpha(agente[i]))
            return 0;
    }
    return 1;
}

void insert(struct Agente A){
    struct Node *t, *temp;

    counter++;
    t = (struct Node*)malloc(sizeof(struct Node));

    if(head == NULL){
        head = t;
        head->data = counter;
        head->next = NULL;
        head->A = A;
        return;
    }

    temp = head;

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = t;
    t->data = counter;
    t->A = A;
    t->next = NULL; 
}

void traverse(){
    struct Node *t;

    t = head;

    if(t == NULL){
        printf("La Lista esta vacia \n");
        return;
    }

    printf("La lista tiene %d Agentes \n \n", counter);

    while(t->next != NULL){
        printf("ID del Agente: %d \n", t->data);
        printf("\t Nombre del Agente: %s \n" , t->A.cName);
        printf("\t Apellido del Agente: %s\n" , t->A.cLastName);
        printf("\t Edad del Agente: %d\n" , t->A.iAge);
        for(int i = 0; i < counterActivos; i++){
            printf("\t Activos del Agente: %s\n" , t->A.cActivos[i]);
            printf("\n");
        }
        for(int i = 0; i < counterMisiones; i++){
            printf("\t Misiones del Agente: %s\n" , t->A.cMission[i]);
            printf("\n");
        }
        t = t->next;
        printf("\n-------------------------------------------\n");
    }

    printf("ID del Agente: %d \n", t->data);
    printf("\t Nombre del Agente: %s \n" , t->A.cName);
    printf("\t Apellido del Agente: %s\n" , t->A.cLastName);
    printf("\t Edad del Agente: %d\n" , t->A.iAge);
    for(int i = 0; i < counterActivos; i++){
            printf("\t Activos del Agente: %s\n" , t->A.cActivos[i]);
            printf("\n");
    }
    for(int i = 0; i < counterMisiones; i++){
            printf("\t Misiones del Agente: %s\n" , t->A.cMission[i]);
            printf("\n");
    }
    printf("\n-------------------------------------------\n");

}

void delete(int x){
    struct Node *prev, *temp;
    temp = head;
    prev = head;

    if(temp != NULL && temp->data == x){
        head = temp->next;
        free(temp);
        return;
    }

    while(temp != NULL && temp->data != x){
        prev = temp; 
        temp = temp->next; 
    }
    if (temp == NULL) return;

    prev->next = temp->next; 
    free(temp);
}