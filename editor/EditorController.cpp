#include <gdk/gdk.h>
#include "EditorWindow.h"
#include "EditorLayer.h"
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "LevelWriter.h"
#include "EditorController.h"

#include <iostream>

EditorController::EditorController(Gtk::Entry *players_size)
  : players_size_(players_size)
  , level_(new Level("Mapa de ejemplo", 1000, 1000))
  , unsaved_changes_(false) {
}

void EditorController::start_new_level() {
  if (unsaved_changes_) {
  // TODO(Diego): mostrar cuadro de dialogo - guardar cambios?
  }
    std::cout << "Archivo -> Nuevo" << std::endl;
}

void EditorController::start_new_level(const Glib::VariantBase& /* parameter */) {
  start_new_level();
}

void EditorController::save_file() {
  LevelWriter writer(*level_);
  writer.write("level1.xml", players_size_->get_text());
}

void EditorController::save_file(const Glib::VariantBase& /* parameter */) {
  save_file();
}

// TODO(Diego): IMPORTANTE!!! EL CONTROLLER ES EL DUEÑO DEL LevelObject Y TIENE QUE LIBERAR
// LA MEMORIA!!
void EditorController::register_object(LevelObject* object) {
  obj_by_rep_lookup_table[object->representation()] = object;
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

EditorController::~EditorController() {
  if (level_) {
    delete level_;
  }
}
