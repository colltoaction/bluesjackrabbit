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
  return engine_steps_ >= MIN_ENGINE_STEPS_TO_SHOOT;
}

void GameObjectPlayer::increase_step() {
  engine_steps_++;
}

void GameObjectPlayer::shot() {
  engine_steps_ = 0;
}

void GameObjectPlayer::update_fixed(Vector gravity) {
  if (!normal_) {
    body().apply_force(gravity);
  }
  normal_ = false;
}

void GameObjectPlayer::impact(GameObject *other) {
  switch (other->game_object_type()) {
    case 'f':
      // body().stop();
      normal_ = true;
      break;
    case 'b':
      lives_--;
      break;
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
