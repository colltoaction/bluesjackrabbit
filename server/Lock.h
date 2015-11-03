#ifndef BLUESJACKRABBIT_COMMON_LOCK_H
#define BLUESJACKRABBIT_COMMON_LOCK_H

#include "Mutex.h"

class Lock {
 private:
  Mutex *mutex;
 public:
  explicit Lock(Mutex *mutex);
  ~Lock();
};

#endif /* BLUESJACKRABBIT_COMMON_LOCK_H */
