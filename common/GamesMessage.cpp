#include "GamesMessage.h"
#include "Logger.h"
#include "Constants.h"

#define MAX_NAME_LENGTH 256


GamesMessage::GamesMessage(Socket *socket)
    : Message(LIST_GAMES)
    , socket_(socket) {
}

char GamesMessage::type_id() {
  return LIST_GAMES;
}

char GamesMessage::type() {
  return Message::type();
}

std::map<size_t, std::string> GamesMessage::read() {
  std::map<size_t, std::string> games;
  char game_count;
  socket_->read_buffer(&game_count, sizeof(char));
  for (char i = 0; i < game_count; i++) {
    char game_id;
    socket_->read_buffer(&game_id, sizeof(char));
    char game_name_length;
    socket_->read_buffer(&game_name_length, sizeof(char));
    char game_name[MAX_NAME_LENGTH];
    socket_->read_buffer(game_name, game_name_length);
    game_name[static_cast<size_t>(game_name_length)] = '\0';
    games[game_id] = game_name;
  }

  Logger::info("Read available games");
  return games;
}

void GamesMessage::send(const std::map<char, std::string> &games) {
  char game_count = static_cast<char>(games.size());
  socket_->send_buffer(&game_count, sizeof(char));
  for (std::map<char, std::string>::const_iterator it = games.begin();
       it != games.end(); it++) {
    char game_id = it->first;
    socket_->send_buffer(&game_id, sizeof(char));
    char game_name_length = static_cast<char>(it->second.size());
    socket_->send_buffer(&game_name_length, sizeof(char));
    socket_->send_buffer(it->second.c_str(), game_name_length);
  }

  Logger::info("Sent available games");
}
