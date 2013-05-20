#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "clientTask.h"
#include "queue.h"

clientTask::clientTask(int fd ) {
    socketFd = fd;
    dbNumber=1;
}

void clientTask::go() {
    int runFlag = 1;
    int bytecount = -1;
    int errorFlag = 0;
    int cnt = 0;
    int tokenCount = 0;
    int tokenLength = 0;

    myQueue cmd;
    while( 1 == runFlag ) {
        //        tokenCount = 0;
        //        tokenLength = 0;

        bytecount = readline(socketFd,inBuffer,sizeof(inBuffer));
        if( -1 == bytecount ) {
            fprintf(stderr, "Error receiving data %d\n", errno);
            errorFlag = -1;
            runFlag =0;
        }
        if( 0 == bytecount ) {
            runFlag == 0;
            errorFlag = 0;
        }

        printf("Received bytes %d\nReceived string\n>%s<\n", bytecount, inBuffer);

        if ( (tokenCount != 0 ) && (tokenLength != 0) && (cnt > 0)) {
            printf("cmd=%s\n",inBuffer);
            cnt--;
            tokenLength = 0;

            cmd.add( inBuffer );
        }

        if( inBuffer[0] == '*' ) {
            tokenCount = atoi(&inBuffer[1]);
            cnt = tokenCount;
        }

        if(inBuffer[0] == '$' ) {
            tokenLength = atoi(&inBuffer[1]);
        }

        if( cnt == 0) {
            tokenCount = 0;
            tokenLength = 0;
            // 
            // Now command is assembled in the queue
            // Call the parser.
            //
            printf("DONE\n\n");
            cmd.dump();
            sprintf(outBuffer,"+OK\r\n");
            write( socketFd, outBuffer,strlen(outBuffer));
            printf("%s",outBuffer);
        }

    } //  while

}

void clientTask::dump() {
}

clientTask::~clientTask() {
}

int clientTask::readline( int fd, char *ptr, int maxLen ) {
    int n;
    int cnt = 0;
    int runFlag = 1;
    char c;


    do {
        n = read(fd,&c,1);
        if( n <= 0) {
            runFlag=0;
        }
        if ( '\n' == c ) {
            runFlag=0;
            ptr[cnt]= '\0';
        } else if ( '\r' == c  ) {

        } else {
            ptr[cnt++]=c;
        }
        if (cnt > maxLen ) {
            runFlag = 0;
        }
    }
    while( runFlag != 0);
    return(cnt);
}


