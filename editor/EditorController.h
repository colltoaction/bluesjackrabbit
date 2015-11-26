#ifndef BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#define BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H

#include "EditorLayer.h"

class EditorController {
 public:
  EditorController();
  void start_new_level();
  void start_new_level(const Glib::VariantBase&);
 private:
  // Level level_;
  bool unsaved_changes_;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
