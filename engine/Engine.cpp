#include <glibmm/main.h>
#include <vector>
#include "Engine.h"
#include "GameObjectBullet.h"
#include "RigidBody.h"
#include "StaticBody.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "GameObjectPlayer.h"

Engine::Engine() {
  game_objects_.emplace_back(new GameObject(Vector::zero()));
  game_objects_.emplace_back(new GameObject(Vector(20, 0)));
  game_objects_.emplace_back(new GameObject(Vector(0, 20)));
  Glib::signal_timeout().connect(
      sigc::bind_return(sigc::mem_fun(*this, &Engine::FixedUpdate), true),
      fixedUpdateStep);
}

std::vector<GameObject*> &Engine::game_objects() {
  return game_objects_;
}

std::map<uint32_t, GameObject*> &Engine::game_objects() {
  return game_objects_;
}
void Engine::FixedUpdate() {
//    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
  for (std::vector<GameObject*>::iterator game_object = game_objects_.begin();
       game_object != game_objects_.end();
       ++game_object) {
    (*game_object)->rigid_body().update_fixed();
    (*game_object)->update_fixed();
    if (collides(game_object)) {
      (*game_object)->rigid_body().bounce();
      // TODO(tinchou): don't call this twice
      (*game_object)->update_fixed();
    }
  }
}

bool Engine::collides(const std::vector<GameObject*>::iterator &game_object) {
  for (std::vector<GameObject*>::iterator other = game_objects_.begin();
       other != game_objects_.end();
       ++other) {
    if (game_object != other) {
      if ((*game_object)->collides(**other)) {
        return true;
      }
    }
  }

  return false;
}

void Engine::apply_force(GameObject *game_object, Vector force) {
  game_object->rigid_body().apply_force(force);
}
