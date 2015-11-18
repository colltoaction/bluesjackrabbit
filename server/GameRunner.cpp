#include "GameRunner.h"

#include <common/Lock.h>
#include <common/Logger.h>
#include <unistd.h>
#include <iostream>

#include "Constants.h"

#define SECOND_TO_MICROSECONDS 1000000.0
#define TWENTY_MILLIS_IN_MICROSECONDS 20000.0

const double GameRunner::step = 0.003;

GameRunner::GameRunner(Engine *engine, std::map<char, ClientProxy*> *players)
  : engine_(engine),
    engine_mutex_(),
    players_(players),
    keep_running_(true),
    game_finished_(false) {
}

GameRunner::~GameRunner() {
}

void GameRunner::run() {
  while (keep_running_ && !game_finished_) {
    notify_clients(true);
    game_loop();
  }
}

void GameRunner::game_loop() {
  while (keep_running_) {
    clock_t start = clock();
    engine_step();
    clock_t stop = clock();
    double elapsed = static_cast<double>(stop - start)* SECOND_TO_MICROSECONDS / CLOCKS_PER_SEC;
    if (elapsed > TWENTY_MILLIS_IN_MICROSECONDS) {
      Logger::warning("Engine too slow to run in 20 milliseconds");
    }
    usleep(static_cast<__useconds_t>(TWENTY_MILLIS_IN_MICROSECONDS - elapsed));
  }
}

void GameRunner::engine_step() {
  Lock lock(&engine_mutex_);
  engine_->FixedUpdate();
  notify_clients(false);
  engine_->clean_dead();
}

void GameRunner::notify_clients(bool notify_object_ids) {
  for (std::map<char, ClientProxy*>::iterator it = players_->begin();
      it != players_->end();
      it++) {
    if (notify_object_ids) {
      // Called the first time server notifies clients game objects
      char object_size = static_cast<char>(engine_->game_objects().size());
      it->second->send_object_size(object_size);
    }
    for (std::map<uint32_t, GameObject*>::iterator game_it = engine_->game_objects().begin();
              game_it != engine_->game_objects().end();
              game_it++) {
      it->second->send_object(game_it->first, game_it->second);
    }
  }
}

void GameRunner::action(uint32_t object_id, char option) {
  Lock lock(&engine_mutex_);
  // std::cout << "Game::action apply force obj id: " << static_cast<int>(object_id) << std::endl;
  if (option == LEFT) {
    engine_->apply_force_(object_id, Vector(-step, 0));
  } else if (option == RIGHT) {
    engine_->apply_force_(object_id, Vector(step, 0));
  } else if (option == DOWN) {
    engine_->apply_force_(object_id, Vector(0, step));
  } else if (option == UP) {
    engine_->apply_force_(object_id, Vector(0, -step));
  }
}

void GameRunner::shoot(uint32_t object_id) {
  Lock lock(&engine_mutex_);
  engine_->player_shoot(object_id);
}

void GameRunner::finalize() {
  keep_running_ = false;
}
