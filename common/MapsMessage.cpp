#include "MapsMessage.h"
#include "Logger.h"

MapsMessage::MapsMessage(Socket *socket)
    : socket_(socket) {
}

std::list<char> MapsMessage::read() {
  std::list<char> maps;
  char map_count;
  socket_->read_buffer(&map_count, sizeof(char));
  for (char i = 0; i < map_count; i++) {
    char map_id;
    socket_->read_buffer(&map_id, sizeof(char));
    maps.push_back(map_id);
  }

  Logger::info("Read available maps");
  return maps;
}

void MapsMessage::send(const std::list<char> &maps) {
  char map_count = static_cast<char>(maps.size());
  socket_->send_buffer(&map_count, sizeof(char));
  for (std::list<char>::const_iterator map_id = maps.begin();
       map_id != maps.end(); map_id++) {
    socket_->send_buffer(&(*map_id), sizeof(char));
  }

  Logger::info("Sent available maps");
}
