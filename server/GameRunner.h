#ifndef BLUESJACKRABBIT_SERVER_GAMERUNNER_H
#define BLUESJACKRABBIT_SERVER_GAMERUNNER_H

#include <map>

#include <common/Mutex.h>
#include <common/Thread.h>
#include <engine/Engine.h>

#include "ClientProxy.h"

class GameRunner: public Thread {
 public:
  GameRunner(Engine *engine, std::map<char, ClientProxy*> *players, Mutex *engine_mutex);
  virtual ~GameRunner();
  virtual void run();
  void finalize();

 private:
  Engine *engine_;
  Mutex *engine_mutex_;
  std::map<char, ClientProxy*> *players_;
  bool keep_running_;
  bool game_finished_;

  void game_loop();
  void engine_step();
  void notify_clients(bool notify_object_ids);
};

#endif /* BLUESJACKRABBIT_SERVER_GAMERUNNER_H */
