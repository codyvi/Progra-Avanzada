//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 18/02/2020
//Menu donde se guardan los datos de los agentes, se pueden desplegar, agregar o borrar.

#include "stdlib.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "time.h"

//struct usada para guardar los datos del agente
struct Agent{
    char cNombre[30];
    char cUNombre[30];
    int iEdad;
    char cGenero[12];
    char cMision[12][12];
    char cActivos[13][13];
};
//Struct usada para acceder a los datos del agente
struct Node{
    int data;
    struct Node *next;
    struct Agent A;
};

//Variables Globales 
struct Node *head = NULL;
int counter = 0;
int counterActivos = 0;
int counterMisiones = 0;
int ArrActivos[13];
int ArrMisiones[13];

//Funcion para validar los activos 
int checkActivos(char agente[13])
{
    int i = 0;
    
    for(; i < 4; i++)
    {
        if(!isalpha(agente[i]))
            return 0;
    }
    
    for(; i < 13; i++)
    {
        if(!isdigit(agente[i]))
            return 0;
    }
    return 1;
}
//funcion para checar que el formato de las misiones este bien
int checkMisiones(char mision[12])
{
    int i = 0;
    for(; i < 3; i++)
    {
        if(!isalpha(mision[i]))
            return 0;
    }

    for(; i < 12; i++)
    {
        if(!isdigit(mision[i]))
            return 0;
    }
    return 1;
}

//Función añadida para agregar agente a la lista
void add(struct Agent A)
{
    struct Node *t, *temp;

    counter++;
    t = (struct Node*)malloc(sizeof(struct Node));

    if(head == NULL)
    {
        head = t;
        head->data = counter;
        head->next = NULL;
        head->A = A;
        return;
    }

    temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = t;
    t->data = counter;
    t->A = A;
    t->next = NULL; 
}

//Función para poder imprimir la lista
void traverse()
{
    struct Node *List;

    List = head;

    if(List == NULL)
    {
        printf("No hay nadie en la lista \n");
        return;
    }

    printf("La lista tiene %d Agentes \n \n", counter);

    while(List->next != NULL)
    {
        printf("ID del Agente: %d \n", List->data);
        printf("\t Nombre del Agente: %s \n" , List->A.cNombre);
        printf("\t Apellido del Agente: %s\n" , List->A.cUNombre);
        printf("\t Edad del Agente: %d\n" , List->A.iEdad);
        for(int i = 0; i < counterActivos; i++)
        {
            printf("\t Activos del Agente: %s\n" , List->A.cActivos[i]);
            printf("\n");
        }

        for(int i = 0; i < counterMisiones; i++)
        {
            printf("\t Misiones del Agente: %s\n" , List->A.cMision[i]);
            printf("\n");
        }

        List = List->next;
        printf("\n-------------------------------------------\n");
    }

    printf("ID del Agente: %d \n", List->data);
    printf("\t Nombre del Agente: %s \n" , List->A.cNombre);
    printf("\t Apellido del Agente: %s\n" , List->A.cUNombre);
    printf("\t Edad del Agente: %d\n" , List->A.iEdad);

    for(int i = 0; i < counterActivos; i++)
    {
            printf("\t Activos del Agente: %s\n" , List->A.cActivos[i]);
            printf("\n");
    }

    for(int i = 0; i < counterMisiones; i++)
    {
            printf("\t Misiones del Agente: %s\n" , List->A.cMision[i]);
            printf("\n");
    }
    printf("\n-------------------------------------------\n");

}

//Función para borrar un agente de la lista
void delete(int x)
{
    struct Node *prev, *tmp;
    tmp = head;
    prev = head;

    if(tmp != NULL && tmp->data == x)
    {
        head = tmp->next;
        free(tmp);
        return;
    }

    while(tmp != NULL && tmp->data != x)
    {
        prev = tmp; 
        tmp = tmp->next; 
    }
    if (tmp == NULL) return;

    prev->next = tmp->next; 
    free(tmp);
}

//funcion principal
int main()
{
    int iInput;
    int CounterAgentes = 0;
    int iDAta;
    int iNumActivos;
    int iNumMisiones;
    char buf[10]; //Variable temporal
    printf("\n-------------------------------------------\n");
    printf("\n------------Bienvenido agente--------------\n");
    printf("\n-------------------------------------------\n");


    for(;;)
    {
        struct Agent P;
        printf("\n-------------------------------------------\n");
        printf("1. Agregar a un nuevo agente \n");
        printf("2. Borrar un agente\n");
        printf("3. Mostrar a los agentes\n");
        printf("4. Salir y borrar todo\n");
        scanf("%d", &iInput);

        // iInput = atoi(buf);

        if(iInput == 1)
        {
            // printf("\n Opcion uno \n");
            CounterAgentes++;
            fgets(P.cNombre,30,stdin); //fget para que ignore este, y pase al otro, esto por problemas con scanf
            printf("%s\n", "Introduce el nombre del agente: ");
            fgets(P.cNombre,30,stdin);
            printf("%s\n", "Introduce el apellido del agente: ");
            fgets(P.cUNombre,30,stdin);
            printf("%s\n", "Introduce la edad del agente: ");
            fgets(buf,10,stdin);
            //Validando que el dato sea int
            while(!atoi(buf))
            {
                printf("Error, escribe un numero \n");
                printf("%s\n", "Introduce la edad del agente: ");
                fgets(buf,10,stdin);
            }

            P.iEdad = atoi(buf);

            printf("%s\n", "Introduce el genero del agente: ");
            fgets(P.cGenero,12,stdin);
            

            printf("Ingresa cuantos activos tiene el agente\n");
            fgets(buf,10,stdin);
            iNumActivos = atoi(buf);
            ArrActivos[CounterAgentes] = iNumActivos;
            while(iNumActivos > 0)
            {
                char cActivos[13] = "";
                printf("Ingresa al activo\n");
                fgets(cActivos,14,stdin);
                // printf("%s", cActivos);
                if(checkActivos(cActivos))
                {
                    strcpy(P.cActivos[counterActivos], cActivos);
                    counterActivos++;
                    printf("Activo agregado de manera exitosa \n");
                    iNumActivos--;
                } 
                
                else 
                {
                    printf("Activo no cumple con el formato\n");
                }
            }

            printf("Ingresa cuantos misiones tiene el agente\n");
            scanf("%d", &iNumMisiones);
            ArrMisiones[CounterAgentes] = iNumMisiones;
            // printf("%d",iNumMisiones);
            while(iNumMisiones > 0)
            {
                char cMission[12] = "";
                printf("Ingresa la mision\n");
                scanf("%s", cMission);
                if(checkMisiones(cMission))
                {
                    strcpy(P.cMision[counterMisiones], cMission);
                    counterMisiones++;
                    printf("Mision agregada de manera exitosa \n");
                    iNumMisiones--;
                } 
                
                else 
                {
                    printf("Mision no cumple con el formato\n");
                }
            }

            add(P);
        }

        else if(iInput == 2)
        {
            // printf("\n Opcion dos \n");            
            traverse();
            if(head != NULL)
            {
                printf("Introduce el ID del elemento a borrar: \n");
                scanf("%d", &iDAta);
                delete(iDAta);
            }
            
        }

        else if(iInput == 3)
        {
            // printf("\n Opcion tres \n");
            traverse();
        }
        
        else if(iInput == 4)
        {
            printf("\n Borrando todo...\n");
            sleep(2);
            printf("\n Listo, adios agente.\n");
            break;
        }
    }



    return 0;
}