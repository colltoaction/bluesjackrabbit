#include <sstream>
#include <string>
#include <vector>
#include <libxml++/libxml++.h>
#include "CircleLevelObject.h"
#include "GenericImageLevelObject.h"
#include "GoalLevelObject.h"
#include "LevelObject.h"
#include "Map.h"
#include "RectangleLevelObject.h"
#include "SpawnPointLevelObject.h"
#include "StartPointLevelObject.h"
#include "LevelWriter.h"

#include <iostream>

LevelWriter::LevelWriter(const Level& level) : level_(level) {
}

void LevelWriter::write(const std::string& file_name) {
  xmlpp::Document document;
  xmlpp::Element* node_root = document.create_root_node("level");
  append_level_to_node(node_root);
  document.write_to_file(file_name);
}

void LevelWriter::write_map(const std::string& file_name, const Map& map) {
  xmlpp::Document document;
  xmlpp::Element* node_root = document.create_root_node("map");
  node_root->set_attribute("players_size", "1");

  std::vector<Level*>::const_iterator it = map.levels().begin();
  for (; it != map.levels().end(); ++it) {
    level_ = **it;
    xmlpp::Element* level_node = node_root->add_child("level");
    append_level_to_node(level_node);
  }

  document.write_to_file(file_name);
}

void LevelWriter::append_level_to_node(xmlpp::Element* node_root) {
  xmlpp::Element* visible_object_layer_node = node_root->add_child("visible-object-layer");
  add_visible_child_nodes(visible_object_layer_node);

  xmlpp::Element* control_object_layer_node = node_root->add_child("control-object-layer");
  add_control_child_nodes(control_object_layer_node);
}

void LevelWriter::add_visible_child_nodes(xmlpp::Element* root_element) {
  const std::vector<LevelObject*> objects = level_.generic_objects();
  std::vector<LevelObject*>::const_iterator it = objects.begin();
  while (it != objects.end()) {
    xmlpp::Element* child_node = NULL;
    switch ((*it)->object_type()) {
    case GENERIC_IMAGE:
      {
        GenericImageLevelObject* obj = static_cast<GenericImageLevelObject*>(*it);
        child_node = root_element->add_child("image");
        child_node->set_attribute("x", to_string(obj->x()));
        child_node->set_attribute("y", to_string(obj->y()));
        child_node->set_attribute("filename", obj->file());
        child_node->set_attribute("rotation", to_string(obj->rotation_angle()));
      }
      break;
    case CIRCLE:
      {
        CircleLevelObject* obj = static_cast<CircleLevelObject*>(*it);
        child_node = root_element->add_child("circle");
        child_node->set_attribute("centrex", to_string(obj->x()));
        child_node->set_attribute("centrey", to_string(obj->y()));
        child_node->set_attribute("radius", to_string(obj->radius()));
      }
      break;
    case BREAKABLE_RECT:
    case RECTANGLE:
      {
        RectangleLevelObject* obj = static_cast<RectangleLevelObject*>(*it);
        child_node = root_element->add_child("rectangle");
        child_node->set_attribute("x", to_string(obj->x()));
        child_node->set_attribute("y", to_string(obj->y()));
        child_node->set_attribute("width", to_string(obj->width()));
        child_node->set_attribute("height", to_string(obj->height()));
        child_node->set_attribute("rotation", to_string(obj->rotation_angle()));
        child_node->set_attribute("breakable", obj->breakable() ? "true" : "false");
      }
      break;
    default:
      break;
    }
    ++it;
  }
}

void LevelWriter::add_control_child_nodes(xmlpp::Element* root_element) {
  add_control_child_nodes_by_type(root_element, "startpoint", level_.start_points());
  add_control_child_nodes_by_type(root_element, "spawnpoint", level_.spawn_points());
  add_control_child_nodes_by_type(root_element, "goal", level_.goals());
}

void LevelWriter::add_control_child_nodes_by_type(xmlpp::Element* root_element,
    std::string elem_type, std::vector<LevelObject*> objects) {
  std::vector<LevelObject*>::const_iterator it = objects.begin();
  while (it != objects.end()) {
    xmlpp::Element* node = root_element->add_child(elem_type);
    node->set_attribute("x", to_string((*it)->x()));
    node->set_attribute("y", to_string((*it)->y()));
    ++it;
  }
}

void LevelWriter::add_metadata_to_node(xmlpp::Element* root_element, LevelObject* obj) {
  std::vector<std::pair<std::string, std::string> > metadata = obj->metadata();
  std::vector<std::pair<std::string, std::string> >::const_iterator cit = metadata.begin();
  xmlpp::Element* meta_node = root_element->add_child("metadata");
  while (cit != metadata.end()) {
    xmlpp::Element* property = meta_node->add_child("property");
    property->set_attribute("key", cit->first);
    property->add_child_text(to_string(cit->second));
    ++cit;
  }
}
