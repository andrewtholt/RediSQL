
class clientTask {

    public:
        clientTask(int );
        ~clientTask();
        void dump();
        void go();
    private:
        int socketFd;
        int dbNumber;
        char inBuffer[1024];
        char outBuffer[1024];
        int readline( int, char *, int );
};
