#include <glibmm/main.h>
#include <vector>
#include "Engine.h"
#include "GameObjectTemplate.h"
#include "RigidBody.h"
#include "StaticBody.h"

#include <iostream>

const Vector Engine::gravity_ = Vector(0, 0.0000098) * fixed_update_step * fixed_update_step;  // in m/ms²

Engine::Engine() {
  std::cout << "Construyendo engine\n";
}

std::vector<GameObject*> &Engine::game_objects() {
  return game_objects_;
}

void Engine::FixedUpdate() {
//    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
  for (std::vector<GameObject*>::iterator game_object = game_objects_.begin();
       game_object != game_objects_.end();
       ++game_object) {
    apply_force(*game_object, gravity_);
    if (will_collide(game_object)) {
      (*game_object)->rigid_body().stop();
    }

    (*game_object)->rigid_body().update_fixed();
    (*game_object)->update_fixed();
  }
}

bool Engine::will_collide(const std::vector<GameObject*>::iterator &game_object) {
  for (std::vector<GameObject*>::iterator other = game_objects_.begin();
       other != game_objects_.end();
       ++other) {
    if (game_object != other) {
      if ((*game_object)->will_collide(**other)) {
        return true;
      }
    }
  }

  return false;
}

void Engine::apply_force(GameObject *game_object, Vector force) {
  game_object->rigid_body().apply_force(force);
}


void Engine::add_game_object(bool is_static, bool circle_collider, const Vector &position) {
  (void) circle_collider;
  if (is_static) {
    game_objects_.push_back(new GameObjectTemplate<StaticBody>(position));
  } else {
    game_objects_.push_back(new GameObjectTemplate<RigidBody>(position));
  }
}

char Engine::objects_size() {
  return static_cast<char>(game_objects_.size());
}
