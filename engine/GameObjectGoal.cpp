#include "GameObjectGoal.h"

GameObjectGoal::GameObjectGoal(Body *body, Collider *collider, WinnerNotifier winner_notifier)
  : GameObject(body, collider)
  , winner_notifier_(winner_notifier) {
}

GameObjectGoal::~GameObjectGoal() {
}

char GameObjectGoal::game_object_type() {
  return 'o';
}

void GameObjectGoal::impact(GameObject *other) {
  if (other->game_object_type() == 'p') {
    winner_notifier_(dynamic_cast<GameObjectPlayer *>(other));
  }
}

bool GameObjectGoal::alive() {
  return true;
}
