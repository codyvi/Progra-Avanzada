//David Alonso Cantu Martinez A00822455
//Practica 17

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 100


typedef struct myThread {
    int id;
    int time;
    int * dependents;
    int array_size;
} myThread;

pthread_t threads[NUM_THREADS];

//Constructor
myThread * Thread(int id, int time, int dependents[100], int array_size){
  myThread * t = malloc(sizeof(myThread));
  t->time = time;
  t->id = id;
  t->dependents = dependents;
  t->array_size = array_size;
  return t;
}

//Convierte el id del Thread a int
int parseThreadId(char * tid){
    int iTid = 0;
    int i = 1;
    while(*tid != '\0'){
        if(isdigit(*tid)){
            iTid += atoi(tid) * i;
            i *= 10;
        }
        tid++;
    }
    return iTid;
}

//Leer las lineas del archivo
int countLinesFromFile(char * file_name){
    int i = 0;
    char tmp[100];
    FILE *f;
    f = fopen(file_name, "r");

    while(fscanf(f, "%s\t%s\t%s\t", tmp, tmp, tmp) != EOF){
        i++;
    }
    fclose(f);
    return i;
}

//Obtener el numero de elementos, numero de dependientes
int count_num_elements(char * orig_value){
    //Si no tiene dependiente se devuelve 0
    if(*orig_value == '-') return 0;

    char * value = malloc(sizeof(orig_value));
    strcpy(value, orig_value);
    int num_elems = 0;
    //Ir haciendo split
    char *pt;
    pt = strtok (value,",");
    while (pt != NULL) {
        num_elems++;
        pt = strtok (NULL, ",");
    }
    free(value);
    return num_elems;
}

//Por el formato es necesario quitarle el nombre del thread
int * separete_elements(char * value, int num_elems){
    //Creamos un arreglo dinamico para guardar los ids
    int * elems = malloc(num_elems * sizeof(int));
    int i = 0;

    //Ir haciendo split
    char *pt;
    pt = strtok(value,",");
    while(pt != NULL){
        //Cambiamos a int
        int num = parseThreadId(pt);
        elems[i] = num;
        i++;
        pt = strtok(NULL, ",");
    }

    return elems;
}


//Obetner los threads del archivo
myThread * * readFileForThreads(char * file_name, int iNumberOfLines){
    //Donde guardaremos el id del thread
    char tid[10];
    //Donde guardamos los diferentes threads a los que depende
    char dependents[100];
    //Tiempo en que tarda el thread y variable controlador para el arreglo
    int tTime, i = 0;
    //Leemos el archivo
    FILE *f;
    //Creamos un arreglo del tamaño necesario para guardar los threads
    myThread * * struct_threads = malloc(iNumberOfLines * sizeof(myThread));
    f = fopen(file_name, "r");

    //Leemos el archivo, por la naturaleza del formato, necesitamos convertirlo
    while(fscanf(f, "%s\t%d\t%s", tid, &tTime, dependents) != EOF){
        int dep_size = count_num_elements(dependents); //Obtener el numero de dependienes
        int * int_dependents = separete_elements(dependents, dep_size); //Obtener el id 
        int iTid = parseThreadId(tid); //Obtener el id del thread
        struct_threads[i++] = Thread(iTid, tTime, int_dependents, dep_size);
    }
    fclose(f);
    return struct_threads;
}

//Funcion principal
void *printHello (void *threadid){
    myThread *thread = (struct myThread*)threadid;
    printf("------Hello World! It’s me, thread #%d!------\n", thread->id);

    for(int i = 0; i < thread->array_size; i++){
        printf("It's me, thread %d, I depend on thread %d \n", thread->id, thread->dependents[i]);
        pthread_join(threads[thread->dependents[i]-1],NULL);
    }


    printf("'''It’s me, thread #%d EXITING!''' \n", thread->id);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    
    char file_name[25];

    printf("Name of the file, with .txt \n");
    scanf("%s", file_name);

    // Numero de lineas del archivo
    int iNumberOfLines = countLinesFromFile(file_name);
    myThread * * thread_list = readFileForThreads(file_name, iNumberOfLines);

    int rc = 0;
    int t = 0;

    for (t = 0; t < iNumberOfLines; t++) {
        printf("In main: creating thread %d\n", thread_list[t]->id);
        rc = pthread_create(threads + t, NULL, printHello, (void *) thread_list[t]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
