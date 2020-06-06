#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>

#include "macro.h"

void run(int sockfd, struct sockaddr *cliaddr, socklen_t clilen)
{
    int n = 0, count = 0, w = 0;
    long received = 0, writed = 0;
    socklen_t len;
    // char buf[MAXLINE];
    FILE *file;
    PACK packet;

    len = clilen;
    n = recvfrom(sockfd, &packet, sizeof(packet), 0, cliaddr, &len);
    abort_on_error(n == -1, "recvfrom() filename error");
    // buf[n] = 0;
    printf("Received from client: [%s]\n", packet.data);

    if(strstr(packet.data, "=rm")){
        printf("%s", "---------------------------------------------------------");
        char trg[256];
        char cmd[512];
        char *temp;
        int status;
        strcpy(trg, packet.data);
        temp = strchr(trg,'=');
        *temp = '\0';
        printf("%s", trg);
        printf("%s", "---------------------------------------------------------");
        status = remove(trg);
        sprintf(cmd, "rm -rf %s", trg);
        system(cmd);
        return;
    } else {
        file = fopen((const char *) packet.data, "w+");
        abort_on_error(file == NULL, "fopen() error");

        // abort_on_error(setvbuf(file, buf, _IOFBF, MAXLINE*MUL), "setvbuf() error");

        packet.seq_num = 0;
        packet.status = 0;
        memset(packet.data, 0, sizeof(packet.data));
        memcpy(packet.data, "ok", strlen("ok"));
        abort_on_error(sendto(sockfd, (struct pkt *) &packet, sizeof(packet), 0, cliaddr, len) == -1,
                    "sendto() ok error");

        memset(packet.data, 0, sizeof(packet.data));
        abort_on_error(recvfrom(sockfd, &packet, sizeof(packet), 0, cliaddr, &len) == -1,
                    "recvfrom() error");
        long filesize = strtol((const char *) packet.data, NULL, 0);
        printf("filesize: %ld\n", filesize);

        int num_packet = filesize / sizeof(packet.data);
        int packet_header_size = sizeof(packet) - sizeof(packet.data);
        int last_size = filesize - num_packet * (n - packet_header_size);

        while ((n = recvfrom(sockfd, &packet, sizeof(packet), 0, cliaddr, &len))) {
            abort_on_error(n == -1, "recvfrom() data error");

            if (!(strcmp((const char *) packet.data, END_FLAG))) {
                printf("END_FLAG received. Stopping receiving data.\n");
                break;
            }

            received += n;
            count += 1;
            // memset(buf, (int) packet.data, sizeof(packet.data));
            printf("Bytes received: %d\n", n);

            // printf("num_packet: %d\n", num_packet);

            if (!num_packet) {
                printf("byte to write: %ld\n", filesize);
                w = fwrite(packet.data, sizeof(char), filesize, file);
                printf("byte writed: %d\n", w);
                writed += w;
            } else {
                if (count <= num_packet) {
                    printf("byte to write: %d\n", n - packet_header_size);
                    w = fwrite(packet.data, sizeof(char), n - packet_header_size, file);
                    printf("byte writed: %d\n", w);
                    writed += w;
                } else {
                    printf("byte to write: %d\n", last_size);
                    w = fwrite(packet.data, sizeof(char), last_size, file);
                    printf("byte writed: %d\n", w);
                    writed += w;
                }
            }
        }
        printf("Tot Bytes writed: %ld\n", writed);
        printf("Tot Bytes received: %ld\n", received);
        fclose(file);
    }
}

int main(int argc, char **argv){
        int sockfd, newsockfd;
        struct sockaddr_in servaddr, cliaddr;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(SERV_PORT);

        bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    while(1){
        listen(sockfd, 5);
        int clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, (unsigned int *) &clilen);

        abort_on_error(newsockfd == -1, "Error accept()");
        run(newsockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
    }
    return 0;
}
