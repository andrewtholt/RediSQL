#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "queue.h"

//
// = qmember methods =========================================
//
qmember::qmember() {
    p = new srep;
}

qmember::qmember(char *ptr) {
    p = new srep;
    p->string = new char[ strlen(ptr) + 1 ];
    strcpy(p->string,ptr);
    p->next = (class qmember *)NULL;
}

qmember::qmember(char *ptr, qmember* l) {
    p = new srep;
    p->string = new char[ strlen(ptr) + 1 ];
    strcpy(p->string,ptr);
    p->next = l;
}

void qmember::print() {
    printf("Hello there\n");
    printf(">%s<\n", p->string);
}

char *qmember::get() {
    return( p->string );
}

void qmember::setNext( qmember *l ) {
    p->next = l;
}

qmember* qmember::getNext() {
    return(p->next);
}

qmember::~qmember() {
    delete p->string;
    delete p;
}
//
// ===========================================================
//
myQueue::myQueue() {
    head=(class qmember *)NULL; // Point to first record
    tail=(class qmember *)NULL; // Point to last
}

void myQueue::add(char *ptr) {

    qmember* cmd;
    cmd = new qmember(ptr);

    if ((struct qmember *)NULL == head ) {
        head = cmd;
        tail = cmd;
    } else {
        tail->setNext( cmd );
        tail = cmd;

    }
}

char *myQueue::get() {
    return( head->get());
}

void myQueue::dump() {
    qmember* entry;

    printf("\nData dump from queue\n");

    if( (class qmember *)NULL == head ) {
        printf("\nEmpty Q\n");
    } else {
        entry=head;

        while( (class qmember *)NULL != entry) {
            printf("Data is %s\n",entry->get());
            entry=entry->getNext();
        }
    }
}

myQueue::~myQueue() {
    qmember* entry;
    entry=head;

    while( (class qmember *)NULL != entry) {
        delete entry;
        entry=entry->getNext();
    }
}

