//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 14/04/2020
//Cliente de TCP para enviar mensajes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

//Funcion para imprimir el error que llegara a pasar
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

//funcion principal
int main(int argc, char *argv[])
{
    int iSockfd, iPortno, iN;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    //Si los argumentos dados son menores a 3, se muestra el uso
    if (argc < 3) 
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    iPortno = atoi(argv[2]);
    iSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (iSockfd < 0) 
        error("ERROR opening socket"); //Si el socket no funciona
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n"); //Si el host no existe
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(iPortno);
    if (connect(iSockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting"); //Error de conexion
    printf("Please enter the message: "); 
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    iN = write(iSockfd,buffer,strlen(buffer));
    if (iN < 0) 
         error("ERROR writing to socket"); //Error al escribir en el puerto
    bzero(buffer,256);
    iN = read(iSockfd,buffer,255);
    if (iN < 0) 
         error("ERROR reading from socket"); //Error al leer del puerto
    printf("%s\n",buffer);
    close(iSockfd);
    return 0;
}
