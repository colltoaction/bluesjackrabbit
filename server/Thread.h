#ifndef BLUESJACKRABBIT_SERVER_THREAD_H
#define BLUESJACKRABBIT_SERVER_THREAD_H

class Thread {
public:
    virtual ~Thread() { }
    void Start();
    void Join();
protected:
    virtual void ThreadMain() = 0;
private:
    pthread_t thread;
    static void* StartRoutine(void* arg);
};

#endif // BLUESJACKRABBIT_SERVER_THREAD_H
