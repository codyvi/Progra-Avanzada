#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include <errno.h>
#include <stdint.h>


#define SERV_PORT 49312
#define MAXLINE   1400

#define END_FLAG "================END"

#define abort_on_error(cond, msg) do {			 		 	   					\
	if (cond) { 											 					\
		fprintf(stderr, "%s (errno=%d [%s])\n", msg, errno, strerror(errno)); 	\
		exit(EXIT_FAILURE); 													\
	} 																			\
} while (0)

struct pkt {
    // struct sockaddr_in addr;
    // int sockfd;
    uint16_t seq_num;
    uint32_t status;
    uint8_t data[MAXLINE];
};

typedef struct pkt PACK;

#endif                          // MACRO_H
