#include "PlayerInfoMessage.h"
#include "Constants.h"

PlayerInfoMessage::PlayerInfoMessage(Socket *socket)
    : Message(PLAYER_INFO)
    , socket_(socket) {
}

char PlayerInfoMessage::type_id() {
  return PLAYER_INFO;
}

char PlayerInfoMessage::type() {
  return Message::type();
}

void PlayerInfoMessage::send(GameObjectPlayer *player) {
  send_char(socket_, player->remaining_lives());
}

void PlayerInfoMessage::read() {
  remaining_lives_ = read_char(socket_);
}

char PlayerInfoMessage::remaining_lives()const {
  return remaining_lives_;
}
