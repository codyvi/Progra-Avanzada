// David Alonso Cantu Martinez
// A00822455
// Daemon solución al problema Sum on Tree de CodeChef
// https://www.codechef.com/problems/TSUM2

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <limits.h>
#include <stdbool.h>
#include <time.h>


FILE *input, *output;

typedef struct Nodes {
    int value;
    int n;
    int *adjacents;
} Node;

//Funcion que devuelve el mas largo
int longest(Node nodes[], bool visited[], int curr, int place) {
    visited[curr] = true;

    int largest = INT_MIN;
    for (int x = 0; x < nodes[curr].n; x++) {
        int adjacent = nodes[curr].adjacents[x];

        if (!visited[adjacent]) {
            int val = longest(nodes, visited, adjacent, place + 1);
            if (largest < val) largest = val;
        }   
    }

    return nodes[curr].value * place + (largest < 0 ? 0 : largest);
}

// Lee los datos del archivo y llama a longest para cada nodo,
int solve() {
    int n;
    fscanf(input, "%d", &n);

    Node nodes[n];

    for (int x = 0; x < n; x++) {
        fscanf(input, "%d", &nodes[x].value);
        nodes[x].adjacents = calloc(n, sizeof(int));
        nodes[x].n = 0;
    }

    for (int x = 0; x < n-1; x++) {
        int start, end;
        fscanf(input, "%d %d", &start, &end);

        nodes[start-1].adjacents[nodes[start-1].n++] = end-1;
        nodes[end-1].adjacents[nodes[end-1].n++] = start-1;
    }

    int largest = INT_MIN;
    for (int x = 0; x < n; x++) {
        bool visited[n];
        int val = longest(nodes, visited, x, 1);
        if (largest < val) largest = val;
    }

    return largest;
}

int main(void) {
        
    /* Our process ID and Session ID */
    pid_t pid, sid;
    
    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
       we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);
            
    /* Open any logs here */        
            
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    
    /* Change the current working directory */
    if ((chdir("/home/david/Documents/Progra-Avanzada/Code/Tarea 16")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    
    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    /* Daemon-specific initialization goes here */
    
    /* The Big Loop */
    while (1) {

        input = fopen("test.txt", "r");
        output = fopen("out.txt", "w");
        int n;

        fscanf(input, "%d", &n);

        for (int x = 0; x < n; x++) {
            int ans = solve();
            printf("%d\n", ans);
            fprintf(output, "%d\r", ans);
        }

        fclose(input);
        fclose(output);
       
       sleep(10); /* wait 10 seconds */
    }
    exit(EXIT_SUCCESS);
}