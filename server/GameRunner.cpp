#include "GameRunner.h"

#include <unistd.h>
#include <iostream>

GameRunner::GameRunner(Engine *engine, std::map<char, ClientProxy*> *players)
  : engine_(engine),
    players_(players),
    keep_running_(true) {
}

GameRunner::~GameRunner() {
}

void GameRunner::run() {
  std::cout << "Runner start running\n";
  while (keep_running_) {
    clock_t begin = clock();
    (void) begin;
    engine_stuff();
    notify_clients();
    usleep(20000);
  }
}

void GameRunner::engine_stuff() {
  // Lock l(mutex);
  engine_->FixedUpdate();
  // engine_->get_diffs();
}

void GameRunner::notify_clients() {
  std::cout << "Runner notificando\n";
  int i = 0;
  for (std::map<char, ClientProxy*>::iterator it = players_->begin();
      it != players_->end();
      it++) {
    std::cout << "obteniendo game object\n";
    GameObject *object = NULL;
    if (i == 0) {
      object = engine_->game_objects().front();
    } else {
      object = engine_->game_objects().back();
    }
    std::cout << "Enviando game object position\n";
    it->second->send_object_position(object);
    i++;
  }
}

void GameRunner::finalize() {
  keep_running_ = false;
}
