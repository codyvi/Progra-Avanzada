#define _DEFAULT_SOURCE
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
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/inotify.h>
#include <sys/stat.h>

#include "macro.h"

FILE *input, *output;


void clientCall() {
     while(1) {
        char *hostname = "localhost";
        int sockfd, n, sent;
        long count = 0;
        struct sockaddr_in servaddr;
        // char buf[MAXLINE];
        char *target, *path;
        FILE *file;
        PACK packet;
        long filesize;
        char trg[256];

        bzero(&servaddr, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(SERV_PORT);
        inet_pton(AF_INET, hostname, &servaddr.sin_addr);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        abort_on_error(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0,
                    "Error connect()");

        int fd = inotify_init();
        char buf[sizeof(struct inotify_event) + NAME_MAX + 1];
        struct inotify_event * evp;

        if(fd < 0){
            perror("inotify_init():");
            //return -1;
        }

        int watchfd = inotify_add_watch(fd, ".", IN_MODIFY | IN_CREATE | IN_DELETE);
        while(1) {
            read(fd, buf, sizeof(buf));
            evp = (struct inotify_event * )buf;

            if (evp->len > 0) {
                if (evp->mask & IN_DELETE) {
                    path = evp->name;
                    printf("The file %s was deleted.\n", path);
                    strcpy(trg, path);
                    strcat(trg, "=rm");
                    memset(packet.data, 0, sizeof(packet.data));
                    memcpy(packet.data, trg, strlen(trg));
                    break;
                } else if (evp->mask & IN_MODIFY || evp->mask & IN_CREATE ) {
                    if(evp->mask &IN_ISDIR){
                       printf("Directory %s was modified", evp->name); 
                    }
                    else{
                        printf("The file %s was modified.\n", evp->name);
                    }
                    path = evp->name;
                    target = evp->name;
                    memset(packet.data, 0, sizeof(packet.data));
                    memcpy(packet.data, target, strlen(target));
                    break;
                }
            }
        }

        //path = argv[2];
        //target = argv[3];

        packet.seq_num = 0;
        packet.status = 0;

        abort_on_error(sendto
                    (sockfd, (struct pkt *) &packet, sizeof(packet), 0,
                        (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1,
                    "sendto() filename error");
        if(evp->mask & IN_MODIFY || evp->mask & IN_CREATE ){
            memset(packet.data, 0, sizeof(packet.data));
            abort_on_error(recvfrom(sockfd, &packet, sizeof(packet), 0, NULL, NULL) == -1,
                        "recvfrom() ok error");
            if (!strncmp((const char *) packet.data, "ok", 2)) {
                printf("Filename sent.\n");
            }

            file = fopen(path, "r");
            abort_on_error(file == NULL, "fopen() error");
            abort_on_error(fseek(file, 0L, SEEK_END) == -1, "fseek() error");
            filesize = ftell(file);
            printf("filesize: %ld\n", filesize);
            abort_on_error(fseek(file, 0L, SEEK_SET) == -1, "fseek() error");
            memset(packet.data, 0, sizeof(packet.data));
            sprintf((char *) packet.data, "%ld", filesize);

            abort_on_error(sendto
                        (sockfd, (struct pkt *) &packet, sizeof(packet), 0,
                            (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1, "sendto() data error");

            memset(packet.data, 0, sizeof(packet.data));

            while ((n = fread(packet.data, sizeof(char), MAXLINE, file))) 
            {
                abort_on_error(ferror(file), "fread() error");
                abort_on_error((sent =
                                sendto(sockfd, (struct pkt *) &packet, sizeof(packet), 0,
                                    (struct sockaddr *) &servaddr, sizeof(servaddr))) == -1,
                            "sendto() data error");

                count += sent;
                printf("Bytes sent: %d\n", sent);
                memset(packet.data, 0, sizeof(packet.data));
            }
            printf("Tot Bytes sent: %ld\n", count);

            memset(packet.data, 0, sizeof(packet.data));
            memcpy(packet.data, END_FLAG, strlen(END_FLAG));
            abort_on_error(sendto
                        (sockfd, (struct pkt *) &packet, sizeof(packet), 0,
                            (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1,
                        "sendto() end_flag error");

            fclose(file);
            //return 0;
        }
    }
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
    if ((chdir("/home/david/Documents/M6/client")) < 0) {
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
        clientCall();
        sleep(1); /* wait 10 seconds */
    }
    exit(EXIT_SUCCESS);
}