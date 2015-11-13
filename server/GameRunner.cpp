#include "GameRunner.h"

#include <common/Lock.h>
#include <unistd.h>
#include <iostream>

#define SECOND_TO_MICROSECONDS 1000000.0
#define TWENTY_MICROSECONDS 20000.0

GameRunner::GameRunner(Engine *engine, std::map<char, ClientProxy*> *players, Mutex *engine_mutex)
  : engine_(engine),
    engine_mutex_(engine_mutex),
    players_(players),
    keep_running_(true) {
}

GameRunner::~GameRunner() {
}

void GameRunner::run() {
  std::cout << "Runner start running\n";
  while (keep_running_) {
    clock_t start = clock();
    engine_step();
    clock_t stop = clock();
    double elapsed = static_cast<double>(stop - start)* SECOND_TO_MICROSECONDS / CLOCKS_PER_SEC;
    usleep(static_cast<__useconds_t>(TWENTY_MICROSECONDS - elapsed));
  }
}

void GameRunner::engine_step() {
  Lock lock(engine_mutex_);
  engine_->FixedUpdate();
  notify_clients();
}

void GameRunner::notify_clients() {
  for (std::map<char, ClientProxy*>::iterator it = players_->begin();
      it != players_->end();
      it++) {
    for (std::map<char, GameObject*>::iterator game_it = engine_->game_objects().begin();
              game_it != engine_->game_objects().end();
              game_it++) {
      it->second->send_object_position(game_it->first, game_it->second);
    }
  }
}

void GameRunner::finalize() {
  keep_running_ = false;
}
