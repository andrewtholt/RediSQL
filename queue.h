#include <stdio.h>

struct qmember {
    char *string;
    struct qmember *next;
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
