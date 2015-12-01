#ifndef BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#define BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
#include <vector>
#include <map>
#include <gtkmm/entry.h>
#include <glibmm/refptr.h>
#include "Level.h"
#include "LevelObject.h"
#include "EditorLayer.h"

class EditorController {
 public:
  EditorController(Gtk::Entry *players_size);
  ~EditorController();
  void start_new_level();
  void start_new_level(const Glib::VariantBase&);
  void save_file();
  void save_file(const Glib::VariantBase&);
  void register_object(LevelObject* object);
  // void update_object(Glib::RefPtr<Goocanvas::Item>, int x, )

 private:
  Gtk::Entry *players_size_;
  Level* level_;
  bool unsaved_changes_;
  std::map<Glib::RefPtr<Goocanvas::Item>*, LevelObject*> obj_by_rep_lookup_table;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCONTROLLER_H
