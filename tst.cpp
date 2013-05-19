#include "queue.h"

int main() {
    myQueue cmd;
    cmd.add((char *)"HELLO");
    cmd.add((char *)"THERE");
    cmd.add((char *)"ANDREW");
    cmd.dump();
    return(0);
}
