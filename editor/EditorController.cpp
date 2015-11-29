#include <gdk/gdk.h>
#include "EditorWindow.h"
#include "EditorLayer.h"
#include "LevelObject.h"
#include "EditorController.h"

#include <iostream>

EditorController::EditorController() : unsaved_changes_(false) {
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

// TODO(Diego): IMPORTANTE!!! EL CONTROLLER ES EL DUEÑO DEL LevelObject Y TIENE QUE LIBERAR
// LA MEMORIA!!
void EditorController::register_object(LevelObject* object) {
  std::cout << "Registrando objeto con direccion " << object << std::endl;
  objects_.push_back(object);
  obj_by_rep_lookup_table[object->representation()] = object;
}
