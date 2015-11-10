#include <glibmm/main.h>
#include <vector>
#include "Engine.h"
#include "GameObjectTemplate.h"
#include "RigidBody.h"
#include "StaticBody.h"

const Vector Engine::gravity_ = Vector(0, 0.001);

Engine::Engine() {
  game_objects_.push_back(new GameObjectTemplate<RigidBody>(Vector::zero()));
  game_objects_.push_back(new GameObjectTemplate<StaticBody>(Vector(5, 0)));
  game_objects_.push_back(new GameObjectTemplate<StaticBody>(Vector(0, 5)));
  Glib::signal_timeout().connect(
      sigc::bind_return(sigc::mem_fun(*this, &Engine::FixedUpdate), true),
      fixedUpdateStep);
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
