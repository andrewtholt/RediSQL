#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include <map>
#include <string>

#include "clientTask.h"

using namespace std;

/*
 * TODO
 * 1. Get rid of the goto's
 *
 */

void* SocketHandler(void*);

void* tst() {
}

int main(int argv, char** argc){

	int host_port= 1101;

	struct sockaddr_in my_addr;

	int hsock;
	int * p_int ;
	int err;

	socklen_t addr_size = 0;
	int* csock;
	sockaddr_in sadr;
	pthread_t thread_id=0;
    map<string, void (*)> cmdMap;


	hsock = socket(AF_INET, SOCK_STREAM, 0);
	if(hsock == -1){
		printf("Error initializing socket %d\n", errno);
		goto FINISH;
	}
	
	p_int = (int*)malloc(sizeof(int));
	*p_int = 1;
		
	if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
		(setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
		printf("Error setting options %d\n", errno);
		free(p_int);
		goto FINISH;
	}
	free(p_int);

	my_addr.sin_family = AF_INET ;
	my_addr.sin_port = htons(host_port);
	
	memset(&(my_addr.sin_zero), 0, 8);
	my_addr.sin_addr.s_addr = INADDR_ANY ;
	
	if( bind( hsock, (sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
		fprintf(stderr,"Error binding to socket, make sure nothing else is listening on this port %d\n",errno);
		goto FINISH;
	}
	if(listen( hsock, 10) == -1 ){
		fprintf(stderr, "Error listening %d\n",errno);
		goto FINISH;
	}

    // OK, no all that works, lets set up the command table.
    //

    cmdMap["info"] = tst;

	//Now lets do the server stuff

	addr_size = sizeof(sockaddr_in);
	
	while(true){
		printf("waiting for a connection\n");
		csock = (int*)malloc(sizeof(int));
		if((*csock = accept( hsock, (sockaddr*)&sadr, &addr_size))!= -1){
			printf("---------------------\nReceived connection from %s\n",inet_ntoa(sadr.sin_addr));
			pthread_create(&thread_id,0,&SocketHandler, (void*)csock );
			pthread_detach(thread_id);
		}
		else{
			fprintf(stderr, "Error accepting %d\n", errno);
		}
	}
	
FINISH:
;
}

int readline( int fd, char *ptr, int maxLen ) {
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


void* SocketHandler(void* lp){
    int *csock = (int *)lp;

	char buffer[1024];
    char outBuffer[1024];
	int buffer_len = 1024;
	int bytecount;

    clientTask tasker(*csock);
    tasker.go();
    /*
	memset(buffer, 0, buffer_len);

	if((bytecount = readline(*csock,buffer,buffer_len)) == -1) {
		fprintf(stderr, "Error receiving data %d\n", errno);
		goto FINISH;
	}
	printf("Received bytes %d\nReceived string \"%s\"\n", bytecount, buffer);
	sprintf(buffer, "SERVER ECHO\n");


	if((bytecount = send(*csock, buffer, strlen(buffer), 0))== -1){
		fprintf(stderr, "Error sending data %d\n", errno);
		goto FINISH;
	}
	
	printf("Sent bytes %d\n", bytecount);
    */


FINISH:
	free(csock);
    return 0;
}
