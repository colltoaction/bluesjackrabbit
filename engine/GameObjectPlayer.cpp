#include "GameObjectPlayer.h"
#define MIN_ENGINE_STEPS_TO_SHOOT 50
#define LIVES 4

GameObjectPlayer::GameObjectPlayer(Body *body, Collider *collider)
  : GameObject(body, collider), engine_steps_(0), lives_(LIVES), direction_(1),
    normal_(false) {
}

GameObjectPlayer::~GameObjectPlayer() {
}

char GameObjectPlayer::game_object_type() {
  return 'p';
}

bool GameObjectPlayer::can_shoot() {
  return engine_steps_ - last_shot_ >= MIN_ENGINE_STEPS_TO_SHOOT;
}

void GameObjectPlayer::shot() {
  last_shot_ = engine_steps_;
}

void GameObjectPlayer::update_fixed(Vector gravity) {
  engine_steps_++;
  if (!normal_) {
    body().apply_force(gravity);
  } else {
    body().stop_y();
  }
  normal_ = false;
}

void GameObjectPlayer::impact(GameObject *other) {
  switch (other->game_object_type()) {
    case 'f':
      normal_ = true;
      break;
    case 'b':
    case 't':
    case 'r':
      lives_--;
      break;
  }
}

bool GameObjectPlayer::alive() {
  return lives_ != 0;
}

char GameObjectPlayer::direction() {
  return direction_;
}

void GameObjectPlayer::new_direction(bool right) {
  direction_ = (right) ? 1 : -1;
}
