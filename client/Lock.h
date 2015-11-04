#ifndef BLUESJACKRABBIT_COMMON_LOCK_H
#define BLUESJACKRABBIT_COMMON_LOCK_H

#include "Mutex.h"

class Lock {
 public:
  explicit Lock(Mutex *mutex);
  ~Lock();
 private:
  Mutex *mutex;
};

#endif /* BLUESJACKRABBIT_COMMON_LOCK_H */
