#include "MapsMessage.h"
#include "Logger.h"
#include "Constants.h"

MapsMessage::MapsMessage(Socket *socket)
    : Message(LIST_MAPS)
    , socket_(socket) {
}

char MapsMessage::type_id() {
  return LIST_MAPS;
}

char MapsMessage::type() {
  return Message::type();
}

std::list<char> MapsMessage::read() {
  std::list<char> maps;
  char map_count;
  socket_->read_buffer(&map_count, sizeof(char));
  std::stringstream ss;
  ss << "Available map count: " << static_cast<int>(map_count);
  Logger::info(ss.str());
  for (char i = 0; i < map_count; i++) {
    char map_id;
    Logger::info("Reading map");
    socket_->read_buffer(&map_id, sizeof(char));
    maps.push_back(map_id);
    Logger::info("Reading map ended");
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
