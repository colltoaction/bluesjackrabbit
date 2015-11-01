#include <pthread.h>
#include "Thread.h"


void* Thread::StartRoutine(void* arg) {
    Thread* self = (Thread*)arg;
    self->ThreadMain();
    return NULL;
}

void Thread::start() {
    pthread_create(&thread, NULL, Thread::StartRoutine, this);
}

void Thread::join() {
    pthread_join(thread, NULL);
}
