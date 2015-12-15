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
#include "Map.h"

class EditorController {
 public:
  EditorController();
  ~EditorController();
  void start_new_level();
  void start_new_level(const Glib::VariantBase&);
  void load_level();
  void save_file(const std::string& file_name);
  void save_file(const Glib::VariantBase&);
  void export_map(const std::string& file_name);
  void export_map(const Glib::VariantBase&);
  void register_object(LevelObject* object);
  LevelObject* get_registered_object(uint64_t object_id);

 private:
  Map* map_;
  Level* level_;
  std::string level_file_name_;
  bool unsaved_changes_;
  std::map<uint64_t, LevelObject*> obj_by_id_lookup_table_;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
