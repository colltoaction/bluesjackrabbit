#include "GameRunner.h"

#include <unistd.h>
#include <iostream>

GameRunner::GameRunner(Engine *engine, std::map<char, ClientProxy*> *players)
  : engine_(engine),
    players_(players),
    keep_running_(true) {
  std::cout << "Runner construido\n";
}

GameRunner::~GameRunner() {
}

void GameRunner::run() {
  std::cout << "Iterando\n";
  while (keep_running_) {
    clock_t begin = clock();
    (void) begin;
    engine_stuff();
    notify_clients();
    usleep(1000);
  }
}

void GameRunner::engine_stuff() {
  // Lock l(mutex);
  // engine_->update();
  // engine_->get_diffs();
}

void GameRunner::notify_clients() {
  std::cout << "Notificando\n";
  for (std::map<char, ClientProxy*>::iterator it = players_->begin();
      it != players_->end();
      it++) {
    it->second->send_object_position(&engine_->game_objects().front());
  }
}

void GameRunner::finalize() {
  keep_running_ = false;
}
