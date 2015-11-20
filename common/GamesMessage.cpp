#include "GamesMessage.h"
#include "Logger.h"

#define MAX_NAME_LENGTH 256


GamesMessage::GamesMessage(Socket *socket)
    : socket_(socket) {
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

void GamesMessage::send(const std::map<size_t, std::string> &games) {
  (void)games;  // UNUSED
//  char game_count = static_cast<char>(games.size());
//  socket_->send_buffer(&game_count, sizeof(char));
//  for (std::map<size_t, std::string>::const_iterator game_id = games.begin();
//       game_id != games.end(); game_id++) {
//    socket_->send_buffer(&(*game_id), sizeof(char));
//  }
//
//  Logger::info("Sent available games");
}
