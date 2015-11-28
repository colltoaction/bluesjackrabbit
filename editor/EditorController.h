#ifndef BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#define BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#include <vector>
#include <map>
#include <glibmm/refptr.h>
#include "LevelObject.h"
#include "EditorLayer.h"

class EditorController {
 public:
  EditorController();
  void start_new_level();
  void start_new_level(const Glib::VariantBase&);
  void register_object(LevelObject* object);
  bool prueba(const Glib::RefPtr<Goocanvas::Item>& item, GdkEventButton* event);

 private:
  // Level level_;
  bool unsaved_changes_;
  std::map<Glib::RefPtr<Goocanvas::Item>, LevelObject*> obj_by_rep_lookup_table;
  std::vector<LevelObject*> objects_;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
