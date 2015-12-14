#ifndef BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#define BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#include <map>
#include <vector>
#include <stdint.h>
#include <gtkmm/entry.h>
#include <glibmm/refptr.h>
#include "Level.h"
#include "LevelObject.h"
#include "EditorLayer.h"

class EditorController {
 public:
  EditorController();
  ~EditorController();
  void start_new_level();
  void start_new_level(const Glib::VariantBase&);
  void save_file();
  void save_file(const Glib::VariantBase&);
  void register_object(LevelObject* object);
  LevelObject* get_registered_object(uint64_t object_id);

 private:
  Level* level_;
  bool unsaved_changes_;
  std::map<uint64_t, LevelObject*> obj_by_id_lookup_table_;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
