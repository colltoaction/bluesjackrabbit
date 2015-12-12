#ifndef BLUESJACKRABBIT_COMMON_MAPLOADER_H
#define BLUESJACKRABBIT_COMMON_MAPLOADER_H

#include <engine/Engine.h>
#include <engine/GameObjectGoal.h>
#include <map>
#include <server/ClientProxy.h>
#include <libxml++/parsers/domparser.h>
#include <sstream>
#include <string>

class MapLoader {
 public:
  MapLoader(Engine *engine, WinnerNotifier winner_notifier);
  virtual ~MapLoader();
  void load();
  void place_player(ClientProxy *player);
  char needed_players();
  bool load_next_level();
  void reload_level();

 private:
  Engine *engine_;
  WinnerNotifier winner_notifier_;
  bool even_;
  int startpoint_cursor_;
  std::map<uint32_t, ClientProxy*> players_;
  void load_level();
  void reposition_players();
  std::vector<Vector*> start_points_;
  char players_size_;
  xmlpp::DomParser parser_;
  xmlpp::Node::NodeList levels_;
  xmlpp::Node::NodeList::const_iterator level_;

  Vector *player_start_point();
  void add_floor(xmlpp::Node *const & node);
  void add_startpoint(xmlpp::Node *const &node);
  void add_spawnpoint(xmlpp::Node *const &node);
  void add_goal(xmlpp::Node *const &node);

  double to_double(std::string val);
  double to_game_coordinates(std::string val);
};

#endif  // BLUESJACKRABBIT_COMMON_MAPLOADER_H
