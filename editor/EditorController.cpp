#include <gdk/gdk.h>
#include "EditorWindow.h"
#include "EditorLayer.h"
#include "LevelObject.h"
#include "LevelWriter.h"
#include "EditorController.h"

#include <iostream>

EditorController::EditorController() : level_(1000, 1000), unsaved_changes_(false) {
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
  LevelWriter writer(level_);
  writer.write("level1.xml");
}

void EditorController::save_file(const Glib::VariantBase& /* parameter */) {
  save_file();
}

// TODO(Diego): IMPORTANTE!!! EL CONTROLLER ES EL DUEÑO DEL LevelObject Y TIENE QUE LIBERAR
// LA MEMORIA!!
void EditorController::register_object(LevelObject* object) {
  obj_by_rep_lookup_table[object->representation()] = object;
  level_.add_generic_object(object);
}
