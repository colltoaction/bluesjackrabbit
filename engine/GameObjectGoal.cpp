#include "GameObjectGoal.h"

#include <iostream>

GameObjectGoal::GameObjectGoal(Body *body, Collider *collider, WinnerNotifier winner_notifier)
  : GameObject(body, collider)
  , has_winner_(false)
  , winner_notifier_(winner_notifier) {
  std::cout << "Construyendo goal\n";
}

GameObjectGoal::~GameObjectGoal() {
  std::cout << "Destruyendo goal\n";
  std::cout << "Este goal " << (has_winner_ ? "tenia" : "NO tenia") << " ganador\n";
}

char GameObjectGoal::game_object_type() {
  return 'o';
}

void GameObjectGoal::impact(GameObject *other) {
  if (other->game_object_type() == 'p' && !has_winner_) {
    std::cout << "Un jugador llego a la meta\n";
    has_winner_ = true;  // This is set because sometimes we call impact twice per engine step
    winner_notifier_(dynamic_cast<GameObjectPlayer *>(other));
  }
}

bool GameObjectGoal::alive() {
  return true;
}
