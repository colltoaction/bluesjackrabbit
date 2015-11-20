#include "CreateGameMessage.h"

CreateGameMessage::CreateGameMessage(Socket *socket)
    : socket_(socket) {
}

void CreateGameMessage::send(size_t map_id, const std::string &game_name) {
  char map_id_char = static_cast<char>(map_id);
  socket_->send_buffer(&map_id_char, sizeof(char));
  char game_name_length = static_cast<char>(game_name.size());
  socket_->send_buffer(&game_name_length, sizeof(char));
  socket_->send_buffer(game_name.c_str(), game_name_length);
}

void CreateGameMessage::read() {
  socket_->read_buffer(&map_id_, sizeof(char));
  char game_name_length;
  socket_->read_buffer(&game_name_length, sizeof(char));
  socket_->read_buffer(game_name_, game_name_length);
  game_name_[static_cast<size_t>(game_name_length)] = '\0';
}

char CreateGameMessage::map_id() {
  return map_id_;
}

std::string CreateGameMessage::game_name() {
  return game_name_;
}
