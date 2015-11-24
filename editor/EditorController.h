#ifndef BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#define BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H

#include "EditorLayer.h"

class EditorController {
 public:
  EditorController();
  void start_new_level();
  void start_new_level(const Glib::VariantBase&);
  void change_layer(int parameter);
  void tilemap_visible();
  EditorLayer active_layer() {return active_layer_;}
 private:
  // Level level_;
  bool unsaved_changes_;

  EditorLayer active_layer_;

};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
