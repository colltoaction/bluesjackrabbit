#include "GameRunner.h"

#include <common/Lock.h>
#include <common/Logger.h>
#include <unistd.h>

#include <common/Constants.h>
#include <common/MessageWriter.h>

#define SECOND_TO_MICROSECONDS 1000000.0
#define TWENTY_MILLIS_IN_MICROSECONDS 20000.0

const double GameRunner::step = 0.003;

#include <iostream>

GameRunner::GameRunner(Engine *engine, std::map<char, ClientProxy*> *players,
    LoadNextLevelCall load_level_functor)
  : engine_(engine)
  , engine_mutex_()
  , players_(players)
  , levels_won_()
  , keep_running_(true)
  , notify_winner_(false)
  , winner_(NULL)
  , load_level_(load_level_functor) {
}

GameRunner::~GameRunner() {
}

void GameRunner::run() {
  while (keep_running_) {
    clock_t start = clock();
    engine_step();  // notifies clients inside
    clock_t stop = clock();
    double elapsed = static_cast<double>(stop - start)* SECOND_TO_MICROSECONDS / CLOCKS_PER_SEC;
    if (elapsed > TWENTY_MILLIS_IN_MICROSECONDS) {
      Logger::warning("Engine too slow to run in 20 milliseconds");
    }
    if (notify_winner_ || engine_->level_finished()) {
      really_notify_winner();
    }
    usleep(static_cast<__useconds_t>(TWENTY_MILLIS_IN_MICROSECONDS - elapsed));
  }
}

void GameRunner::engine_step() {
  Lock lock(&engine_mutex_);
  engine_->FixedUpdate();
  update_clients();
  // Because clients have to be notified, cant clean dead objects before
  engine_->clean_dead();
}

void GameRunner::action(uint32_t object_id, char option) {
  Lock lock(&engine_mutex_);
  if (option == LEFT) {
    engine_->apply_force_(object_id, Vector(-step, 0));
    engine_->update_player_direction(object_id, false);
  } else if (option == RIGHT) {
    engine_->apply_force_(object_id, Vector(step, 0));
    engine_->update_player_direction(object_id, true);
  } else if (option == DOWN) {
    engine_->apply_force_(object_id, Vector(0, step));
  } else if (option == UP) {
    engine_->apply_force_(object_id, Vector(0, -step));
  }
}

void GameRunner::jump(uint32_t object_id) {
  Lock lock(&engine_mutex_);
  engine_->player_jump(object_id);
}

void GameRunner::shoot(uint32_t object_id) {
  Lock lock(&engine_mutex_);
  engine_->player_shoot(object_id);
}

void GameRunner::notify_winner(GameObjectPlayer *winner) {
  // do not lock
  notify_winner_to_clients(winner);
}

GameObjectPlayer* GameRunner::look_up_winner() {
  GameObjectPlayer *winner = levels_won_.begin()->first;
  int max = levels_won_.begin()->second;
  for (std::map<GameObjectPlayer*, int>::iterator it = levels_won_.begin();
      it != levels_won_.end();
      it++) {
    if (it->second > max) {
      winner = it->first;
      max = it->second;
    }
  }
  return winner;
}

void GameRunner::next_level(bool there_was_winner) {
  keep_running_ = load_level_(there_was_winner);
  if (!keep_running_) {
    GameObjectPlayer *winner = look_up_winner();
    for (std::map<char, ClientProxy*>::iterator it = players_->begin();
         it != players_->end();
         it++) {
      it->second->send_total_winner(winner);
    }
    Logger::info("Game finished");
  }
}

void GameRunner::finalize() {
  keep_running_ = false;
}

void GameRunner::update_clients() {
  for (std::map<char, ClientProxy*>::iterator it = players_->begin();
       it != players_->end();
       it++) {
    it->second->send_objects(engine_->game_objects());
  }
}

void GameRunner::notify_winner_to_clients(GameObjectPlayer *winner) {
  if (levels_won_.find(winner) == levels_won_.end()) {
    levels_won_[winner] = 0;
  }
  levels_won_[winner] += 1;
  notify_winner_ = true;
  winner_ = winner;
}


void GameRunner::really_notify_winner() {
  for (std::map<char, ClientProxy*>::iterator it = players_->begin();
       it != players_->end();
       it++) {
    it->second->send_winner(winner_);
  }
  next_level(winner_ != NULL);
  notify_winner_ = false;
  winner_ = NULL;
}
