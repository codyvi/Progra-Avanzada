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
} Coordinate;

//Structura para guardar las variables de las cordenadas
struct Row
{
    char cLatitude[100];
    char cLongitude[100];
    float iLatitude;
    float iLongitude;
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
int compare(const void *s1, const void *s2)
{
    struct Row *e1 = (struct Row *)s1;
    struct Row *e2 = (struct Row *)s2;
    return e1->iLatitude - e2->iLatitude;
}

//Función principal
int main()
{
    static const char filename[] = "coordinates_pt-1.txt"; //Nombre del archivo que voy a leer
    FILE *file = fopen ( filename, "r" ); //Abriendo el archivo
    Coordinate emp[MAXEMP];
    struct Row row[MAXEMP];
    struct Row rowString[100];
    char number[1024];
    int i = 0;
    int counter = 0;

    //Loop para leer el archivo
    while(fscanf(file, "%s %s %s", emp[i].type, emp[i].str, emp[i].number) != EOF) 
    {
        char output[100];
        if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "N") == 0)
        {
            counter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " North");
            strcpy(row[i].cLatitude, output);
            row[i].iLatitude = atof(emp[i].number);
        }

        else if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "S") == 0)
        {
            counter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " South");
            strcpy(row[i].cLatitude, output);
            row[i].iLatitude = atof(emp[i].number);
        }

        else if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "W") == 0)
        {
            counter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " West");
            strcpy(row[i].cLongitude, output);
            row[i].iLongitude = atof(emp[i].number);
        }

        else if(strcmp(&emp[i].str[strlen(emp[i].str)-1], "E") == 0)
        {
            counter++;
            substr(output, emp[i].str, 0, strlen(emp[i].str)-1);
            strcat(output, " East");
            strcpy(row[i].cLongitude, output);

            row[i].iLongitude = atof(emp[i].number);
        }

        if(i%2 !=0)
        {
            
        }
        i++;

        if(counter%2 == 0)
        {
            printf("\n");
        }
    }

    int k = 1;
    for(int i = 0; i < 200; i++)
    {
        if(i%2 == 0)
        {
            strcpy(rowString[k].cLatitude, row[i].cLatitude);
            strcpy(rowString[k].cLongitude, row[i+1].cLongitude);
            rowString[k].iLatitude =  row[i].iLatitude;
            rowString[k].iLongitude = row[i+1].iLongitude;
            k++;
        };
    }

    qsort(rowString,100, sizeof(struct Row),compare);

 


    FILE * fp; //Variable para guardar los archivos
    fp = fopen ("1.txt","w");

   
    for(int i = 0; i < 100; i++)
    {
        fprintf (fp, "%s %s\n", rowString[i].cLatitude, rowString[i].cLongitude);
    }
    fclose (fp);

    fp = fopen ("2.txt","w");
    
    for(int i = 0; i < 100; i++)
    {
        fprintf (fp, "%f %f\n", rowString[i].iLatitude, rowString[i].iLongitude);
    }
    fclose (fp);
}