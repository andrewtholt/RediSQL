#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "queue.h"

//
// = qmember methods =========================================
//
qmember::qmember() {
    string = (char *)NULL;
    next = (class qmember *)NULL;
}

qmember::qmember(char *ptr) {
    if( (char *)NULL != string ) {
        free(string);
    }

    string = (char *)malloc( strlen( ptr )) ;
    // 
    // Exception ?
    //
}

qmember::~qmember() {
    next=(class qmember *)NULL; // Point to last

    if( (char *)NULL != string ) {
        free(string);
    }
}
//
// ===========================================================
//
myQueue::myQueue() {
    head=(class qmember *)NULL; // Point to first record
    tail=(class qmember *)NULL; // Point to last
}

void myQueue::add(char *ptr) {
    struct qmember *q = (struct qmember *)malloc(sizeof(struct qmember));
    char *data = (char *)malloc(strlen(ptr));

    strcpy(data,ptr);

    q->string = data;

    if ((struct qmember *)NULL == head ) {
        q->next =  (struct qmember *)NULL;
        head = q;
        tail = q;
    } else {
        tail->next = q;
        tail=q;
    }

}

char *myQueue::get() {
}

void myQueue::dump() {
    struct qmember *entry;
    printf("\nData dump from queue\n");

    if( (struct qmember *)NULL == head ) {
        printf("\nEmpty Q\n");
    } else {
        entry=head;

        while( (struct qmember *)NULL != entry) {
            printf("Data is %s\n",entry->string);
            entry=entry->next;
        }
    }
}

myQueue::~myQueue() {
}

/*
int main() {
    myQueue cmd;
    cmd.dump();
    return(0);
}
*/
