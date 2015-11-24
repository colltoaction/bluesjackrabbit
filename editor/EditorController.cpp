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

void EditorController::change_layer(int parameter) {
  switch (static_cast<EditorLayer>(parameter)) {
  case TILEMAP:
    std::cout << "Trabajar con: Tilemap" << std::endl;
    break;
  case OBJECTS:
    std::cout << "Trabajar con: Objects" << std::endl;
    break;
  case CONTROLS:
    std::cout << "Trabajar con: Controls" << std::endl;
    break;
  default:
    break;
  }
}

void EditorController::tilemap_visible() {
  std::cout << "Tilemap" << std::endl;
}
