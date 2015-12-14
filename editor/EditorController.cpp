#include <gdk/gdk.h>
#include "EditorWindow.h"
#include "EditorLayer.h"
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "LevelWriter.h"
#include "EditorController.h"
#include "Map.h"

#include <iostream>

EditorController::EditorController()
    : map_(NULL), level_(new Level("Mapa de ejemplo", 1000, 1000 , 2)),
    level_file_name_("level1.xml"), unsaved_changes_(false) {
}

void EditorController::start_new_level() {
  if (unsaved_changes_) {
  // TODO(Diego): mostrar cuadro de dialogo - guardar cambios?
  }
    // TODO(Diego): pasar a opcion Open
    std::cout << "Archivo -> Nuevo" << std::endl;
    if (level_) {
      delete level_;
    }
    LevelLoader loader;
    level_ = loader.load_level(level_file_name_);
}

void EditorController::start_new_level(const Glib::VariantBase& /* parameter */) {
  start_new_level();
}

void EditorController::save_file(const std::string& file_name) {
  LevelWriter writer(*level_);
<<<<<<< Updated upstream
  writer.write("level1.xml");
=======
  writer.write(file_name);
>>>>>>> Stashed changes
}

void EditorController::save_file(const Glib::VariantBase& /* parameter */) {
  save_file(level_file_name_);
}

void EditorController::register_object(LevelObject* object) {
  std::cout << "Id del item " << object->representation()->item_id() << std::endl;
  obj_by_id_lookup_table_[object->representation()->item_id()] = object;
  switch (object->object_type()) {
  case SPAWN_POINT:
    level_->add_spawn_point(object);
    break;
  case START_POINT:
    level_->add_start_point(object);
    break;
  case GOAL:
    level_->add_goal(object);
    break;
  default:
    level_->add_generic_object(object);
    break;
  }
}

LevelObject* EditorController::get_registered_object(uint64_t object_id) {
  std::cout << "Puntero al item con id " << object_id << ": "
      << obj_by_id_lookup_table_[object_id] << std::endl;
  return obj_by_id_lookup_table_[object_id];
}

EditorController::~EditorController() {
  if (level_) {
    delete level_;
  }
}
