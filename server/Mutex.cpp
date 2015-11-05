#include "Mutex.h"

#include <stdlib.h>
#include <string.h>

Mutex::Mutex() {
  memset(&mutex_, 0, sizeof(pthread_mutex_t));
  pthread_mutex_init(&mutex_, NULL);
}

Mutex::~Mutex() {
  pthread_mutex_destroy(&mutex_);
}

void Mutex::lock() {
  pthread_mutex_lock(&mutex_);
}

void Mutex::unlock() {
  pthread_mutex_unlock(&mutex_);
}
