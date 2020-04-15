//Autor: David Alonso Cantú Martínez
//Matrícula: A00822455
//Fecha: 14/04/2020
//Sevidor de TCP para recibir mensajes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//Funcion para imprimir los errores que sucedan
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//Funcion principal
int main(int argc, char *argv[])
{
     int iSockfd, iNewsockfd, iPortno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     
     int n;
     //Si al momento de correr el programa no se manda el puerto de argumento
     if (argc < 2) 
     {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     iSockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (iSockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     iPortno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(iPortno);
     if (bind(iSockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(iSockfd,5);
     clilen = sizeof(cli_addr);
     iNewsockfd = accept(iSockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (iNewsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     n = read(iNewsockfd,buffer,255);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
     n = write(iNewsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     close(iNewsockfd);
     close(iSockfd);
     return 0; 
}
