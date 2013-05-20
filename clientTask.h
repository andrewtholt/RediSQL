
class clientTask {

    public:
        clientTask(int );
        ~clientTask();
        void dump();
        void go();
    private:
        int socketFd;
        char inBuffer[1024];
        char outBuffer[1024];
};
