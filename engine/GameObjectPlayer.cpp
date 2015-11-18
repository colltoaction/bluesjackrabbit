#include "GameObjectPlayer.h"
#define MIN_ENGINE_STEPS_TO_SHOOT 50
#define LIVES 4

GameObjectPlayer::GameObjectPlayer(Body *body, Collider *collider)
  : GameObject(body, collider), engine_steps_(0), lives_(LIVES) {
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

void GameObjectPlayer::impact(GameObject *other) {
  switch (other->game_object_type()) {
    case 'f':
      body().stop();
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
