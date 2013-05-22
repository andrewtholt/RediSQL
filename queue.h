#include <stdio.h>

#ifndef __QUEUE
#define __QUEUE

class qmember {

    struct srep {
        char *string;
        class qmember *next;
    };

    srep *p;

    public:
        qmember();
        qmember(char *);
        qmember(char *,class qmember *);
        void print();
        char *get();
        void setNext( class qmember *);
        qmember* getNext();
        ~qmember();
};

class myQueue {
    struct qmember *head;
    struct qmember *tail;

    public:
    myQueue();
    void add(char *ptr);
    char *get();
    ~myQueue();
    void dump();
    private:

};
#endif
