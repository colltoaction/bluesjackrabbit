#include "MapsMessage.h"
#include "Logger.h"
#include "Constants.h"

#define MAX_NAME_LENGTH 256


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

std::map<size_t, std::string> MapsMessage::read() {
  std::map<size_t, std::string> maps;
  char map_count;
  socket_->read_buffer(&map_count, sizeof(char));
  std::stringstream ss;
  ss << "Available map count: " << static_cast<int>(map_count);
  Logger::info(ss.str());
  for (char i = 0; i < map_count; i++) {
    Logger::info("Reading map");
    char map_name[MAX_NAME_LENGTH];
    char map_id = read_char(socket_);
    char map_name_length = read_char(socket_);
    socket_->read_buffer(map_name, map_name_length);
    map_name[static_cast<size_t>(map_name_length)] = '\0';
    maps[map_id] = map_name;
    Logger::info("Reading map ended");
  }

  Logger::info("Read available maps");
  return maps;
}

void MapsMessage::send(const std::map<char, std::string> &maps) {
  char map_count = static_cast<char>(maps.size());
  socket_->send_buffer(&map_count, sizeof(char));
  for (std::map<char, std::string>::const_iterator map_it = maps.begin();
       map_it != maps.end(); map_it++) {
    char map_name_length = static_cast<char>(map_it->second.size());
    send_char(socket_, map_it->first);
    send_char(socket_, map_name_length);
    socket_->send_buffer(map_it->second.c_str(), map_name_length);
  }

  Logger::info("Sent available maps");
}
