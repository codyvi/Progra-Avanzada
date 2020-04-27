//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 27/04/2020
//Código para abrir archivo con coordenadas y convertirlas a dos archivos diferentes con formato diferente
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Estructura para determinar que tipo de coordenada es
typedef struct 
{
    char type[10];
    char str[20];
    char number[15];
} Coord;

//Structura para guardar las variables de las cordenadas
struct Vals
{
    char cLat[100];
    char cLon[100];
    float iLat;
    float iLon;
};

enum { MAXEMP = 200 };


//Función para obtener parte del string que quiero
char *substr(char *dst, char *src, size_t offset, size_t length) 
{
    memcpy(dst, src + offset, length);
    dst[length] = '\0';
    return dst;
}

//Funcion para comparar latitudes y definir despues con sort donde van a ir
int cmp(const void *s1, const void *s2)
{
    struct Vals *e1 = (struct Vals *)s1;
    struct Vals *e2 = (struct Vals *)s2;
    return e1->iLat - e2->iLat;
}

//Función principal
int main()
{
    static const char filename[] = "coordinates.txt"; //Nombre del archivo que voy a leer
    FILE *file = fopen ( filename, "r" ); //Abriendo el archivo
    Coord emp[MAXEMP];
    struct Vals row[MAXEMP];
    struct Vals rowString[100];
    char number[1024];
    int i = 0;
    int iCounter = 0;

    //Loop para leer el archivo
    while(fscanf(file, "%s %s %s", emp[i].type, emp[i].str, emp[i].number) != EOF) 
    {
        char output[100];
        if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "N") == 0)
        {
            iCounter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " North");
            strcpy(row[i].cLat, output);
            row[i].iLat = atof(emp[i].number);
        }

        else if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "S") == 0)
        {
            iCounter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " South");
            strcpy(row[i].cLat, output);
            row[i].iLat = atof(emp[i].number);
        }

        else if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "W") == 0)
        {
            iCounter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " West");
            strcpy(row[i].cLon, output);
            row[i].iLon = atof(emp[i].number);
        }

        else if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "E") == 0)
        {
            iCounter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " East");
            strcpy(row[i].cLon, output);

            row[i].iLon = atof(emp[i].number);
        }

        if(i%2 !=0)
        {
            
        }
        i++;

 
    }

    int k = 1;
    for(int i = 0; i < 200; i++)
    {
        if(i%2 == 0)
        {
            strcpy(rowString[k].cLat, row[i].cLat);
            strcpy(rowString[k].cLon, row[i+1].cLon);
            rowString[k].iLat =  row[i].iLat;
            rowString[k].iLon = row[i+1].iLon;
            k++;
        };
    }

    qsort(rowString,100, sizeof(struct Vals),cmp);

 


    FILE * fp; //Variable para guardar los archivos
    fp = fopen ("1.txt","w");

   
    for(int i = 0; i < 100; i++)
    {
        fprintf (fp, "%s %s\n", rowString[i].cLat, rowString[i].cLon);
    }
    fclose (fp);

    fp = fopen ("2.txt","w");
    
    for(int i = 0; i < 100; i++)
    {
        fprintf (fp, "%f %f\n", rowString[i].iLat, rowString[i].iLon);
    }
    fclose (fp);

    printf("Archivos creados");
}