#include "GameObjectPlayer.h"

#define MIN_ENGINE_STEPS_TO_SHOOT 50  // One second
#define MIN_ENGINE_STEPS_TO_DIE 50  // One second
#define LIVES 4

GameObjectPlayer::GameObjectPlayer(Body *body, Collider *collider)
  : GameObject(body, collider)
  , lives_(LIVES)
  , direction_(1) {
}

GameObjectPlayer::~GameObjectPlayer() {
}

char GameObjectPlayer::game_object_type() {
  return 'p';
}

bool GameObjectPlayer::can_jump() {
  return body_->velocity().y() == 0;
}

void GameObjectPlayer::jump() {
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
}

void GameObjectPlayer::impact(GameObject *other) {
  switch (other->game_object_type()) {
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
