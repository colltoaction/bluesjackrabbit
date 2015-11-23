#ifndef BLUESJACKRABBIT_SERVER_GAMERUNNER_H
#define BLUESJACKRABBIT_SERVER_GAMERUNNER_H

#include <map>

#include <common/Thread.h>
#include <engine/Engine.h>

#include "ClientProxy.h"

class GameRunner: public Thread {
 public:
  GameRunner(Engine *engine, std::map<char, ClientProxy*> *players);
  virtual ~GameRunner();
  virtual void run();
  void finalize();

 private:
  Engine *engine_;
  std::map<char, ClientProxy*> *players_;
  bool keep_running_;
  void engine_stuff();
  void notify_clients();
};

#endif /* BLUESJACKRABBIT_SERVER_GAMERUNNER_H */
