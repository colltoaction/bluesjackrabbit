#include <glibmm/main.h>
#include <vector>
#include "Engine.h"
#include "GameObjectBullet.h"
#include "GameObjectNewLife.h"
#include "RigidBody.h"
#include "StaticBody.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include <common/Lock.h>

#include <stdlib.h>

#define SEED 2142585766

Engine::Engine()
  : object_index_(0)
  , seed_(static_cast<unsigned int>(time(NULL))) {
}

Engine::~Engine() {
  for (std::map<uint32_t, GameObject*>::iterator game_object = game_objects_.begin();
         game_object != game_objects_.end();
         ++game_object) {
    delete game_object->second;
  }
}

std::map<uint32_t, GameObject*> *Engine::game_objects() {
  return &game_objects_;
}

void Engine::FixedUpdate() {
  Lock l(&mutex_);
  players_jumps();
  players_shots();
  move_objects();
  rewards();
}

bool Engine::level_finished() {
  bool finished = true;
  for (std::map<uint32_t, GameObjectPlayer*>::iterator it = game_objects_player_ids_.begin();
      it != game_objects_player_ids_.end();
      it++) {
    if (it->second->alive()) {
      finished = false;
    }
  }
  return finished;
}

void Engine::rewards() {
  for (std::map<uint32_t, GameObject*>::iterator other = game_objects_.begin();
      other != game_objects_.end();
      ++other) {
    if (!other->second->alive() && (other->second->game_object_type() == 't'
        || other->second->game_object_type() == 'r')) {
        int probability = rand_r(&seed_) % 10 + 1;
        if (probability > 5) {
          Vector *position = new Vector(other->second->body().position().x(), other->second->body().position().y());
          StaticBody *body = new StaticBody(position);
          GameObjectNewLife *life = new GameObjectNewLife(body, new CircleCollider(body, 0.1));
          add_game_object(life);
        }
    }
  }
  for (std::map<uint32_t, GameObjectPlayer*>::iterator it = game_objects_player_ids_.begin();
      it != game_objects_player_ids_.end();
      it++) {
    it->second->increment_lives();
  }
}

void Engine::clean_dead() {
  std::list<uint32_t> ids;
  for (std::map<uint32_t, GameObject*>::iterator other = game_objects_.begin();
         other != game_objects_.end();
         ++other) {
    if (!other->second->alive() && other->second->game_object_type() != 'p') {
      ids.push_back(other->first);
    }
  }
  for (std::list<uint32_t>::iterator it = ids.begin(); it != ids.end(); it++) {
    GameObject *object = game_objects_[*it];
    game_objects_.erase(*it);
    delete object;
  }
}

void Engine::players_jumps() {
  // Player shoot keeps record of which players shot in this engine step
  for (std::set<uint32_t>::iterator it = player_jump_.begin();
       it != player_jump_.end(); it++) {
      GameObjectPlayer *player = static_cast<GameObjectPlayer*>(game_objects_[*it]);
    if (player->can_jump()) {
      player->jump();
    }
  }

  player_jump_.clear();
}

void Engine::players_shots() {
  // Player shoot keeps record of which players shot in this engine step
  for (std::map<uint32_t, bool>::iterator it = player_shoot_.begin(); it != player_shoot_.end(); it++) {
    if (it->second) {
      GameObjectPlayer *player = static_cast<GameObjectPlayer*>(game_objects_[it->first]);
      if (player->can_shoot()) {
        // Create a new bullet
        Vector origin = game_objects_[it->first]->body().position();
        Vector *offset = new Vector(origin + Vector(player->direction() * 1, 0));
        RigidBody *body = new RigidBody(offset);
        GameObjectBullet *object = new GameObjectBullet(body, new CircleCollider(body, 0.05),
            player->direction());
        game_objects_[object_index_] = object;
        move_object_index();
        player->shot();
      }
      player_shoot_[it->first] = false;
    }
  }
}

void Engine::move_objects() {
  for (std::map<uint32_t, GameObject*>::iterator game_object = game_objects_.begin();
       game_object != game_objects_.end();
       ++game_object) {
    check_collisions(game_object);
    game_object->second->update_fixed();
    // With all forces applied, new position is calculated
    game_object->second->body().update_fixed();
  }
}

void Engine::check_collisions(const std::map<uint32_t, GameObject *>::iterator &game_object) {
  for (std::map<uint32_t, GameObject*>::iterator other = game_objects_.begin();
       other != game_objects_.end();
       ++other) {
    if (game_object != other) {
      if (game_object->second->will_collide(*other->second)) {
        // Make them impact each other
        game_object->second->impact(other->second);
        other->second->impact(game_object->second);
      }
    }
  }
}

void Engine::apply_force(GameObject *game_object, Vector force) {
  game_object->body().apply_force(force);
}

void Engine::update_player_direction(uint32_t object_id, bool right) {
  if (game_objects_.find(object_id) != game_objects_.end()) {
    static_cast<GameObjectPlayer*>(game_objects_[object_id])->new_direction(right);
  }
}

void Engine::apply_force_(uint32_t object_id, Vector force) {
  if (game_objects_.find(object_id) != game_objects_.end()) {
    game_objects_[object_id]->body().apply_force(force);
  }
}

uint32_t Engine::add_game_object(Body *body, Collider *collider) {
  GameObject *game_object = new GameObject(body, collider);
  game_objects_[object_index_] = game_object;
  uint32_t to_return = object_index_;
  move_object_index();
  return to_return;
}

uint32_t Engine::add_game_object(GameObject *game_object) {
  game_objects_[object_index_] = game_object;
  uint32_t to_return = object_index_;
  move_object_index();
  return to_return;
}

uint32_t Engine::add_game_object_player(GameObjectPlayer *game_object) {
  game_objects_[object_index_] = game_object;
  uint32_t to_return = object_index_;
  game_objects_player_ids_[object_index_] = game_object;
  move_object_index();
  return to_return;
}

void Engine::move_game_object_player(uint32_t object_id, const Vector &new_position) {
  static_cast<GameObjectPlayer*>(game_objects_[object_id])->reset_lives();
  game_objects_[object_id]->reposition_object(new_position);
}

void Engine::move_object_index() {
  object_index_++;
  while (game_objects_player_ids_.find(object_index_) != game_objects_player_ids_.end()) {
    object_index_++;
  }
}

void Engine::player_jump(uint32_t object_id) {
  player_jump_.insert(object_id);
}

void Engine::player_shoot(uint32_t object_id) {
  player_shoot_[object_id] = true;
}

void Engine::clean_objects() {
  Lock l(&mutex_);
  for (std::map<uint32_t, GameObject*>::iterator game_object = game_objects_.begin();
         game_object != game_objects_.end();
         ++game_object) {
    if (game_object->second->game_object_type() != 'p') {
      GameObject *object = game_object->second;
      game_objects_.erase(game_object->first);
      delete object;
    }
  }
  reset_object_index();
}

void Engine::reset_object_index() {
  object_index_ = 0;
  while (game_objects_player_ids_.find(object_index_) != game_objects_player_ids_.end()) {
    object_index_++;
  }
}
