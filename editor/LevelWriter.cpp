#include <sstream>
#include <string>
#include <vector>
#include <libxml++/libxml++.h>
#include "CircleLevelObject.h"
#include "GenericImageLevelObject.h"
#include "LevelObject.h"
#include "RectangleLevelObject.h"
#include "LevelWriter.h"

#include <iostream>

LevelWriter::LevelWriter(const Level& level) : level_(level) {
}

void LevelWriter::write(std::string file_name) {
  xmlpp::Document document;
  xmlpp::Element* node_root = document.create_root_node("map");

  xmlpp::Element* title_node = node_root->add_child("title");
  title_node->add_child_text(level_.title());

  xmlpp::Element* width_node = node_root->add_child("width");
  width_node->add_child_text(to_string(level_.width()));

  xmlpp::Element* height_node = node_root->add_child("height");
  height_node->add_child_text(to_string(level_.height()));

  xmlpp::Element* visible_object_layer_node = node_root->add_child("visible-object-layer");
  add_visible_children_nodes(visible_object_layer_node);

  document.write_to_file(file_name);
}

void LevelWriter::add_visible_children_nodes(xmlpp::Element* root_element) {
  const std::vector<LevelObject*> objects = level_.generic_objects();
  std::vector<LevelObject*>::const_iterator it = objects.begin();
  while (it != objects.end()) {
    switch ((*it)->object_type()) {
    case GENERIC_IMAGE:
      {
        GenericImageLevelObject* obj = static_cast<GenericImageLevelObject*>(*it);
        xmlpp::Element* img_node = root_element->add_child("image");
        img_node->set_attribute("x", to_string(obj->x()));
        img_node->set_attribute("y", to_string(obj->y()));
        img_node->set_attribute("filename", obj->file());
        img_node->set_attribute("rotation", to_string(obj->rotation_angle()));
      }
      break;
    case CIRCLE:
      {
        CircleLevelObject* obj = static_cast<CircleLevelObject*>(*it);
        xmlpp::Element* circle_node = root_element->add_child("circle");
        circle_node->set_attribute("centrex", to_string(obj->x()));
        circle_node->set_attribute("centrey", to_string(obj->y()));
        circle_node->set_attribute("radius", to_string(obj->radius()));
      }
      break;
    case RECTANGLE:
      {
        RectangleLevelObject* obj = static_cast<RectangleLevelObject*>(*it);
        xmlpp::Element* rect_node = root_element->add_child("rectangle");
        rect_node->set_attribute("x", to_string(obj->x()));
        rect_node->set_attribute("y", to_string(obj->y()));
        rect_node->set_attribute("width", to_string(obj->width()));
        rect_node->set_attribute("height", to_string(obj->height()));
        rect_node->set_attribute("rotation", to_string(obj->rotation_angle()));
      }
      break;
    default:
      break;
    }
    ++it;
  }
}
