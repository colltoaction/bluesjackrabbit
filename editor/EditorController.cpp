#include "EditorWindow.h"
#include "EditorLayer.h"
#include "EditorController.h"

#include <iostream>

EditorController::EditorController() : unsaved_changes_(false), active_layer_(TILEMAP) {
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
