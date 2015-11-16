#include <glibmm/main.h>
#include <vector>
#include "Engine.h"
#include "RigidBody.h"
#include "StaticBody.h"
#include "CircleCollider.h"
#include "GameObject.h"

#include <iostream>

const Vector Engine::gravity_ = Vector(0, 0.0000098) * fixed_update_step * fixed_update_step;  // in m/ms²

Engine::Engine() : object_index_(0) {
  std::cout << "Construyendo engine\n";
}

Engine::~Engine() {
  for (std::map<char, GameObject*>::iterator game_object = game_objects_.begin();
         game_object != game_objects_.end();
         ++game_object) {
    delete game_object->second;
  }
}

std::map<char, GameObject*> &Engine::game_objects() {
  return game_objects_;
}

void Engine::FixedUpdate() {
//    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
  for (std::map<char, GameObject*>::iterator game_object = game_objects_.begin();
       game_object != game_objects_.end();
       ++game_object) {
    apply_force(game_object->second, gravity_);
    if (will_collide(game_object)) {
      game_object->second->body().stop();
    }

    game_object->second->body().update_fixed();
    game_object->second->update_fixed();
  }
}

bool Engine::will_collide(const std::map<char, GameObject*>::iterator &game_object) {
  for (std::map<char, GameObject*>::iterator other = game_objects_.begin();
       other != game_objects_.end();
       ++other) {
    if (game_object != other) {
      if (game_object->second->will_collide(*other->second)) {
        return true;
      }
    }
  }

  return false;
}

void Engine::apply_force(GameObject *game_object, Vector force) {
  game_object->body().apply_force(force);
}

void Engine::apply_force_(char object_id, Vector force) {
  game_objects_[object_id]->body().apply_force(force);
}

char Engine::add_game_object(Body *body, Collider *collider) {
  GameObject *game_object = new GameObject(body, collider);
  game_objects_[object_index_] = game_object;
  char to_return = object_index_;
  object_index_++;
  return to_return;
}

char Engine::objects_size() {
  return static_cast<char>(game_objects_.size());
}
