#ifndef BLUESJACKRABBIT_COMMON_THREAD_H
#define BLUESJACKRABBIT_COMMON_THREAD_H

#include <pthread.h>

class Thread {
 private:
  pthread_t thread_;
 public:
  Thread();
  virtual ~Thread();
  static void* starter(void *data);
  void start();
  void join();
  virtual void run() = 0;
};

#endif /* BLUESJACKRABBIT_COMMON_THREAD_H */
