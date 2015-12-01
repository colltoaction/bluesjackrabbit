#include "GameObjectPlayer.h"

#define MIN_ENGINE_STEPS_TO_SHOOT 50  // One second
#define MIN_ENGINE_STEPS_TO_DIE 50  // One second
#define LIVES 4

GameObjectPlayer::GameObjectPlayer(Body *body, Collider *collider)
  : GameObject(body, collider)
  , engine_steps_(MIN_ENGINE_STEPS_TO_DIE)
  , last_shot_(MIN_ENGINE_STEPS_TO_SHOOT)
  , last_dead_(MIN_ENGINE_STEPS_TO_DIE)
  , lives_(LIVES)
  , direction_(1)
  , normal_(false)
  , picked_life_(false) {
}

GameObjectPlayer::~GameObjectPlayer() {
}

char GameObjectPlayer::game_object_type() {
  return 'p';
}

bool GameObjectPlayer::can_jump() {
  return alive() && body_->velocity().y() == 0;
}

void GameObjectPlayer::jump() {
  body().apply_jump_force();
}

bool GameObjectPlayer::can_shoot() {
  return alive() && (engine_steps_ - last_shot_ >= MIN_ENGINE_STEPS_TO_SHOOT);
}

void GameObjectPlayer::shot() {
  last_shot_ = engine_steps_;
}

void GameObjectPlayer::update_fixed() {
  engine_steps_++;
}

void GameObjectPlayer::impact(GameObject *other) {
  if (alive()) {
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
      case 'l':
        picked_life_ = true;
        break;
    }
  }
}

bool GameObjectPlayer::alive() {
  return lives_ > 0;
}

char GameObjectPlayer::direction() {
  // TODO(tomas) Esto esta mal porque si me voy deteniendo de a poco.
  // mi velocidad sigue siendo positiva por ej, pero estoy tratando de mirar
  // hacia el otro lado (cosa que deberia poder disparar inmediatamente)
  // Creo que hay que usar position en vez de velocidad, como creo que estaba hecho antes.
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

void GameObjectPlayer::reset_lives() {
  lives_ = LIVES;
}

void GameObjectPlayer::increment_lives() {
  if (picked_life_ && lives_ < LIVES) {
    lives_++;
  }
  picked_life_ = false;
}
