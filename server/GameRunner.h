#ifndef BLUESJACKRABBIT_SERVER_GAMERUNNER_H
#define BLUESJACKRABBIT_SERVER_GAMERUNNER_H

#include <map>

#include <common/Mutex.h>
#include <common/Thread.h>
#include <engine/Engine.h>

#include "ClientProxy.h"

typedef sigc::slot<bool> LoadNextLevelCall;

class GameRunner: public Thread {
 public:
  GameRunner(Engine *engine, std::map<char, ClientProxy*> *players, LoadNextLevelCall load_level_functor);
  virtual ~GameRunner();
  virtual void run();
  void action(uint32_t object_id, char option);
  void jump(uint32_t object_id);
  void shoot(uint32_t object_id);
  void notify_winner(GameObjectPlayer* winner);
  void finalize();

 private:
  Engine *engine_;
  Mutex engine_mutex_;
  std::map<char, ClientProxy*> *players_;
  bool keep_running_;
  bool notify_winner_;
  GameObjectPlayer *winner_;
  LoadNextLevelCall load_level_;
  static const double step;

  bool log_;
  void engine_step();
  void update_clients();
  void notify_winner_to_clients(GameObjectPlayer *winner);
  void next_level();
  void really_notify_winner();
};

#endif /* BLUESJACKRABBIT_SERVER_GAMERUNNER_H */
