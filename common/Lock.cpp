#include "Lock.h"

Lock::Lock(Mutex *mutex) : mutex_(mutex) {
  mutex_->lock();
}

Lock::~Lock() {
  mutex_->unlock();
}

