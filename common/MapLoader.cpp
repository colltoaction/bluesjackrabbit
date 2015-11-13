#include <libxml++/libxml++.h>

#include "MapLoader.h"
#include "Logger.h"

MapLoader::MapLoader(std::string file_name, Engine *engine)
  : file_name_(file_name), engine_(engine) {
}

MapLoader::~MapLoader() {
}

void MapLoader::load() {
  Logger::info("Loading file: " + file_name_);
  xmlpp::DomParser parser;
}
