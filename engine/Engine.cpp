#include <glibmm/main.h>
#include <vector>
#include "Engine.h"
#include "GameObjectBullet.h"
#include "RigidBody.h"
#include "StaticBody.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "GameObjectPlayer.h"

#include <iostream>

const Vector Engine::gravity_ = Vector(0, 0.0000098) * fixed_update_step * fixed_update_step;  // in m/ms²

Engine::Engine() : object_index_(0) {
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
  players_shots();
  move_objects();
}

void Engine::clean_dead() {
  std::list<uint32_t> ids;
  for (std::map<uint32_t, GameObject*>::iterator other = game_objects_.begin();
         other != game_objects_.end();
         ++other) {
    if (!other->second->alive()) {
       ids.push_back(other->first);
    }
  }
  for (std::list<uint32_t>::iterator it = ids.begin(); it != ids.end(); it++) {
    GameObject *object = game_objects_[*it];
    game_objects_.erase(*it);
    delete object;
  }
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
        GameObjectBullet *object = new GameObjectBullet(body, new CircleCollider(*body, 0.05),
            player->direction());
        game_objects_[object_index_++] = object;
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
    // Gravity no more applied here
    // apply_force(game_object->second, gravity_);
    if (will_collide(game_object)) {
      // This is not done anymore because it depends with what you are colliding
      // game_object->second->body().stop();
    }
    // This applies all forces to the object
    game_object->second->update_fixed(gravity_);
    // With all forces applied, new position is calculated
    game_object->second->body().update_fixed();
  }
}

bool Engine::will_collide(const std::map<uint32_t, GameObject*>::iterator &game_object) {
  bool collides = false;
  for (std::map<uint32_t, GameObject*>::iterator other = game_objects_.begin();
       other != game_objects_.end();
       ++other) {
    if (game_object != other) {
      if (game_object->second->will_collide(*other->second)) {
        // Make them impact each other (Cpp does not have multiple dispatch)
        game_object->second->impact(other->second);
        other->second->impact(game_object->second);
        collides = true;
      }
    }
  }
  return collides;
}

void Engine::apply_force(GameObject *game_object, Vector force) {
  game_object->body().apply_force(force);
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
  object_index_++;
  return to_return;
}

uint32_t Engine::add_game_object(GameObject *game_object) {
  game_objects_[object_index_] = game_object;
  uint32_t to_return = object_index_;
  object_index_++;
  return to_return;
}

void Engine::player_shoot(uint32_t object_id) {
  if (game_objects_.find(object_id) != game_objects_.end()) {
    player_shoot_[object_id] = true;
  }
}

uint32_t Engine::objects_size() {
  return static_cast<uint32_t>(game_objects_.size());
}

void Engine::update_player_direction(uint32_t object_id, bool right) {
  if (game_objects_.find(object_id) != game_objects_.end()) {
    static_cast<GameObjectPlayer*>(game_objects_[object_id])->new_direction(right);
  }
}
