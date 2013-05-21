#include <stdio.h>

#ifndef __QUEUE
#define __QUEUE

class qmember {
    public:
        char *string;
        class qmember *next;

        qmember();
        qmember(char *);
        qmember(char *,class qmember *);
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
