#include <engine/Engine.h>
#include <glibmm/main.h>
#include <vector>
#include <stdlib.h>
#include <engine/CircleCollider.h>
#include <engine/PolygonCollider.h>
#include <engine/RigidBody.h>
#include <engine/StaticBody.h>

#include "CharacterRenderer.h"
#include "FloorRenderer.h"
#include "LocalServerProxy.h"
#include "TurtleRenderer.h"


const double LocalServerProxy::step = 0.003;
const double LocalServerProxy::jump_force = 0.003;  // should take into account the physics step

LocalServerProxy::LocalServerProxy() {
  // new objects will be managed by the engine
  RigidBody *b0 = new RigidBody(new Vector(0, 0));
  engine_.add_game_object(b0, new CircleCollider(b0, 5));

  StaticBody *b1 = new StaticBody(new Vector(5, 0));
  engine_.add_game_object(b1, new CircleCollider(b1, 5));

  std::vector<Vector> floor_points;
  floor_points.push_back(Vector(17, 8));
  floor_points.push_back(Vector(17, 4));
  floor_points.push_back(Vector(12, 4));
  floor_points.push_back(Vector(12, 8));
  StaticBody *b2 = new StaticBody(new Vector(0, 5));
  engine_.add_game_object(b2, new PolygonCollider(*b2, floor_points));

  (*engine_.game_objects())[0]->body().position();
  renderers_[0] = new CharacterRenderer((*engine_.game_objects())[0]->body().position(), 0.5);

  uint32_t i = 0;
  for (std::map<uint32_t, GameObject*>::iterator game_object = engine_.game_objects()->begin();
       game_object != engine_.game_objects()->end();
       ++game_object) {
    if (i == 2) {
      std::vector<Vector> points;
      points.push_back(Vector(-2, 4.5));
      points.push_back(Vector(8, 4.5));
      points.push_back(Vector(8, 5.5));
      points.push_back(Vector(-2, 5.5));
      renderers_[i] = new FloorRenderer(game_object->second->body().position(), points);
    } else if (i != 0) {
      renderers_[i] = new TurtleRenderer(game_object->second->body().position(), 0.5, 't');
    }
    i++;
  }

  Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &LocalServerProxy::engine_step),
      Engine::fixed_update_step);
}

LocalServerProxy::~LocalServerProxy() {
  for (std::map<uint32_t, Renderer*>::iterator game_object = renderers_.begin();
       game_object != renderers_.end();
       ++game_object) {
    delete game_object->second;
  }
}

bool LocalServerProxy::engine_step() {
  engine_.FixedUpdate();
  renderers_[0]->update_position((*engine_.game_objects())[0]->body().position());
  return true;
}

void LocalServerProxy::MoveUp() {
  engine_.apply_force_(0, Vector(0, -jump_force));
}

void LocalServerProxy::MoveDown() {
  engine_.apply_force_(0, Vector(0, step));
}

void LocalServerProxy::MoveLeft() {
  engine_.apply_force_(0, Vector(-step, 0));
}

void LocalServerProxy::MoveRight() {
  engine_.apply_force_(0, Vector(step, 0));
}

void LocalServerProxy::jump() {
  engine_.apply_force_(0, Vector(step, step));
}

void LocalServerProxy::shoot() {
  // TODO(tomas) Implementar esto
}

Vector LocalServerProxy::character_position() {
  return (*engine_.game_objects())[0]->body().position();
}

void LocalServerProxy::init_game() {
}

LivesRenderer &LocalServerProxy::lives_renderer() {
  return lives_renderer_;
}

// Nothing, it will be updated from other place
std::map<uint32_t, Renderer*> &LocalServerProxy::renderers() {
  return renderers_;
}

void LocalServerProxy::connect() {
}

std::map<size_t, std::string> LocalServerProxy::list_maps() {
  std::map<size_t, std::string> map;
  map[1] = "Mapa 1";
  map[2] = "Mapa 2";
  map[3] = "Mapa 3";
  return map;
}

std::map<size_t, std::string> LocalServerProxy::list_games() {
  std::map<size_t, std::string> map;
  map[1] = "Juego 1";
  map[2] = "Juego 2";
  map[3] = "Juego 3";
  return map;
}

bool LocalServerProxy::start_game(size_t /* map_id */, std::string /* game_name */, int /*players_size/*/) {
  return true;
}

void LocalServerProxy::join_game(size_t /* game_id */) {
}

void LocalServerProxy::shutdown() {
}

void LocalServerProxy::reset_updater() {
}

void LocalServerProxy::lock_render() {
}

void LocalServerProxy::unlock_render() {
}
