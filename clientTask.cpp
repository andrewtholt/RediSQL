
#include "clientTask.h"

clientTask::clientTask(int fd ) {
    socketFd = fd;
}

void clientTask::go() {
    int runFlag = 1;

    while( 1 == runFlag ) {
    }
}

void clientTask::dump() {
}

clientTask::~clientTask() {
}
