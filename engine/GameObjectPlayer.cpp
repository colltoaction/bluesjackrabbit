#include "GameObjectPlayer.h"

#define MIN_ENGINE_STEPS_TO_SHOOT 50  // One second
#define MIN_ENGINE_STEPS_TO_DIE 50  // One second
#define LIVES 4

GameObjectPlayer::GameObjectPlayer(Body *body, Collider *collider)
  : GameObject(body, collider)
  , can_jump_(true)
  , lives_(LIVES)
  , direction_(1)
  , normal_(false) {
}

GameObjectPlayer::~GameObjectPlayer() {
}

char GameObjectPlayer::game_object_type() {
  return 'p';
}

bool GameObjectPlayer::can_jump() {
  return can_jump_;
}

void GameObjectPlayer::jump() {
  can_jump_ = false;
  body().apply_jump_force();
}

bool GameObjectPlayer::can_shoot() {
  return engine_steps_ - last_shot_ >= MIN_ENGINE_STEPS_TO_SHOOT;
}

void GameObjectPlayer::shot() {
  last_shot_ = engine_steps_;
}

void GameObjectPlayer::update_fixed() {
  engine_steps_++;
  if (!normal_) {
    body().apply_force(gravity_);
  } else {
    body().stop_y();
  }
  normal_ = false;
}

void GameObjectPlayer::impact(GameObject *other) {
  switch (other->game_object_type()) {
    case 'f':
      can_jump_ = true;
      normal_ = true;
      break;
    case 'b':
    case 't':
    case 'r':
      // prevent dying immediately after dying
      if (engine_steps_ - last_dead_ >= MIN_ENGINE_STEPS_TO_DIE) {
        lives_--;
        last_dead_ = engine_steps_;
      }
      break;
  }
}

bool GameObjectPlayer::alive() {
  return lives_ > 0;
}

char GameObjectPlayer::direction() {
  if (body().velocity().x() > 0) {
    return (direction_ = 1);  // update and return
  } else if (body().velocity().x() < 0) {
    return (direction_ = -1);  // update and return
  } else {
    return direction_;  // last direction if it's still
  }
}

char GameObjectPlayer::remaining_lives() {
  return lives_;
}
