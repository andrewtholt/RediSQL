#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>

#include "config.h"

#define MAXLINE 79
/*
 * Connect to a shared memory segment that is created in main.
 * Needs to be protected by a semaphore.
 */

void catch(int snum) {
    int pid;
    int status;

    pid=wait(&status);

    printf("Child exited with status\n", status);
}

int readline( int fd, char *ptr, int maxLen ) {
    int n;
    int cnt = 0;
    int runFlag = 1;

    do {
        n = read(fd,&ptr[cnt],1);

        if( n <= 0) {
            exit(1);
        }

        if ( '\n' == ptr[cnt] ) {
            runFlag=0;
            ptr[cnt]= '\0';
        } else {
            cnt++;
        }

        if (cnt > maxLen ) {
            runFlag = 0;
        }
    }
    while( runFlag != 0);
    return(cnt);
}


void doprocessing (int sock) {
    int n;
    char inBuffer[256];
    char outBuffer[256];
    int runFlag=1;
    int errFlag=0;

    int argCount=-1;
    int argLen=-1;


    while( runFlag) {
        bzero(inBuffer,256);

//        n = read(sock,inBuffer,255);
//        printf("Readline.\n");
        n = readline(sock,inBuffer,255);
        printf("Readline returned %d\n", n);

        if (n < 0) {
            perror("ERROR reading from socket");
            runFlag = 0;
            errFlag=1;
        }

        if( 0 == n ) {
            runFlag=0;
            errFlag=0;
        }

        if( n > 0) {
            printf("Here is the message: >%s<\n",inBuffer);

            if( inBuffer[0] == '*' ) {
                argCount= atoi( &inBuffer[1]) ;
                printf("Number of arguments = %d\n",argCount);
            }
            if( inBuffer[0] == '$' ) {
                argLen= atoi( &inBuffer[1]) ;
                printf("Argument Len = %d\n",argLen);
            }
        }

        if (n < 0) {
            perror("ERROR writing to socket");
            runFlag = 0;
            errFlag=1;
        }
    }
    exit( errFlag );
}


int main( int argc, char *argv[] ) {

    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int  n;
    pid_t pid;

    printf("\nRediSQL Started\n");

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    printf("Port=%d\n", portno);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    /* Now start listening for the clients, here 
     * process will go in sleep mode and will wait 
     * for the incoming connection
     */
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    signal(SIGCHLD,catch);
    while (1) {
        newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
        }
        /* Create child process */
        pid = fork();

        if (pid < 0) {
            perror("ERROR on fork");
            exit(1);
        }

        if (pid == 0)  {
            /* This is the client process */
            close(sockfd);
            doprocessing(newsockfd);
        } else {
            close(newsockfd);
        }
    } /* end of while */
}

