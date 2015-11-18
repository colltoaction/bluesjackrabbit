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

std::map<uint32_t, GameObject*> &Engine::game_objects() {
  return game_objects_;
}

void Engine::players_shots() {
  for (std::map<uint32_t, bool>::iterator it = player_shoot_.begin(); it != player_shoot_.end(); it++) {
    if (it->second) {
      GameObjectPlayer *player = static_cast<GameObjectPlayer*>(game_objects_[it->first]);
      player->increase_step();
      if (player->can_shoot()) {
        Vector origin = game_objects_[it->first]->body().position();
        Vector *offset = new Vector(origin + Vector(4, 0));
        RigidBody *body = new RigidBody(offset);
        GameObjectBullet *object = new GameObjectBullet(body, new CircleCollider(*body, 0.5));
        game_objects_[object_index_++] = object;
        player->shot();
      }
      player_shoot_[it->first] = false;
    }
  }
}

void Engine::FixedUpdate() {
  players_shots();
  for (std::map<uint32_t, GameObject*>::iterator game_object = game_objects_.begin();
       game_object != game_objects_.end();
       ++game_object) {
    apply_force(game_object->second, gravity_);
    if (will_collide(game_object)) {
      // game_object->second->body().stop();
    }
    game_object->second->body().update_fixed();
    game_object->second->update_fixed();
  }
}

bool Engine::will_collide(const std::map<uint32_t, GameObject*>::iterator &game_object) {
  bool collides = false;
  for (std::map<uint32_t, GameObject*>::iterator other = game_objects_.begin();
       other != game_objects_.end();
       ++other) {
    if (game_object != other) {
      if (game_object->second->will_collide(*other->second)) {
        game_object->second->impact(other->second);
        other->second->impact(game_object->second);
        collides = true;
      }
    }
  }
  return collides;
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

void Engine::apply_force(GameObject *game_object, Vector force) {
  game_object->body().apply_force(force);
}

void Engine::apply_force_(uint32_t object_id, Vector force) {
  game_objects_[object_id]->body().apply_force(force);
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
  player_shoot_[object_id] = true;
  // Despues vemos si esto es necesario
  /*Vector origin = game_objects_[object_id]->body().position();
  Vector *offset = new Vector(origin + Vector(4, 0));
  RigidBody *body = new RigidBody(offset);
  GameObjectBullet *object = new GameObjectBullet(body, new CircleCollider(*body));
  game_objects_[object_index_++] = object;*/
}

uint32_t Engine::objects_size() {
  return static_cast<uint32_t>(game_objects_.size());
}
