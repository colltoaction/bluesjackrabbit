#include <pthread.h>
#include "Thread.h"


void* Thread::StartRoutine(void* arg) {
    Thread* self = reinterpret_cast<Thread*>(arg);
    self->ThreadMain();
    return NULL;
}

void Thread::Start() {
    pthread_create(&thread, NULL, Thread::StartRoutine, this);
}

void Thread::Join() {
    pthread_join(thread, NULL);
}
