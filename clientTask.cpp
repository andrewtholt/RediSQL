#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "clientTask.h"

clientTask::clientTask(int fd ) {
    socketFd = fd;
}

void clientTask::go() {
    int runFlag = 1;
    int bytecount = -1;

    while( 1 == runFlag ) {
        if((bytecount = readline(socketFd,inBuffer,sizeof(inBuffer))) == -1) {
            fprintf(stderr, "Error receiving data %d\n", errno);
            runFlag =0;
        }

        printf("Received bytes %d\nReceived string\n>%s<\n", bytecount, inBuffer);
    }
}

void clientTask::dump() {
}

clientTask::~clientTask() {
}

int clientTask::readline( int fd, char *ptr, int maxLen ) {
    int n;
    int cnt = 0;
    int runFlag = 1;

    do {
        n = read(fd,&ptr[cnt],1);
        if( n <= 0) {
            runFlag=0;
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


