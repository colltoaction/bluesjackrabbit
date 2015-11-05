#include "Thread.h"

#include <string.h>

Thread::Thread() {
  memset(&thread_, 0, sizeof(pthread_t));
}

Thread::~Thread() {
}

void* Thread::starter(void *data) {
  (static_cast<Thread*>(data))->run();
  return NULL;
}

void Thread::start() {
  pthread_create(&thread_, NULL, Thread::starter, static_cast<void*> (this));
}

void Thread::join() {
  pthread_join(thread_, NULL);
}
