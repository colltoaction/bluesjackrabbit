#include <libxml++/libxml++.h>
#include "Level.h"
#include "LevelLoader.h"

Level* LevelLoader::load_level(const std::string& level_file_name) {
  parser_.parse_file(level_file_name);
  xmlpp::Node* level_node = parser_.get_document()->get_root_node();
  level_ = new Level(
    level_node->eval_to_string("@title"),
    static_cast<int>(level_node->eval_to_number("@width")),
    static_cast<int>(level_node->eval_to_number("@height")),
    static_cast<int>(level_node->eval_to_number("@players_size")));

  xmlpp::Node *visible_layer = (level_node)->get_first_child("visible-object-layer");
  const xmlpp::Node::NodeList &rectangles = visible_layer->get_children("rectangle");
  for (std::list<xmlpp::Node *>::const_iterator it = rectangles.begin();
       it != rectangles.end(); ++it) {
    add_floor(*it);
  }

  xmlpp::Node *control_layer = (level_node)->get_first_child("control-object-layer");
  const xmlpp::Node::NodeList &startpoints = control_layer->get_children("startpoint");
  for (std::list<xmlpp::Node *>::const_iterator it = startpoints.begin();
       it != startpoints.end(); ++it) {
    add_startpoint(*it);
  }

  const xmlpp::Node::NodeList &spawnpoints = control_layer->get_children("spawnpoint");
  for (std::list<xmlpp::Node *>::const_iterator it = spawnpoints.begin();
       it != spawnpoints.end(); ++it) {
    add_spawnpoint(*it);
  }

  const xmlpp::Node::NodeList &goals = control_layer->get_children("goal");
  for (std::list<xmlpp::Node *>::const_iterator it = goals.begin();
       it != goals.end(); ++it) {
    add_goal(*it);
  }

  return level_;
}

void LevelLoader::add_floor(const xmlpp::Node* /* node */) {
}

void LevelLoader::add_startpoint(const xmlpp::Node* /* node */) {}
void LevelLoader::add_spawnpoint(const xmlpp::Node* /* node */) {}
void LevelLoader::add_goal(const xmlpp::Node* /* node */) {}
