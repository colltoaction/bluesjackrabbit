#ifndef BLUESJACKRABBIT_COMMON_MUTEX_H
#define BLUESJACKRABBIT_COMMON_MUTEX_H

#include <pthread.h>

class Mutex {
 private:
  pthread_mutex_t mutex_;
 public:
  Mutex();
  ~Mutex();
  void lock();
  void unlock();
};

#endif /* BLUESJACKRABBIT_COMMON_MUTEX_H */
