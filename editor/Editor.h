#ifndef BLUESJACKRABBIT_EDITOR_EDITOR_H
#define BLUESJACKRABBIT_EDITOR_EDITOR_H
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolitemgroup.h>
#include <gtkmm/toolpalette.h>
#include <gtkmm/window.h>
// #include "Level.h"

class Editor : public Gtk::Window {
 public:
	Editor();
	virtual ~Editor();
	void start_new_level();

 private:
 	void load_content_from_glade();
 	void init_palette();

 	// Level level_;
 	bool unsaved_changes_;

	
	Gtk::Box* root_;
	
	Gtk::ToolPalette* palette_;
  Gtk::ToolItemGroup* tiles_group_;
  Gtk::ToolItemGroup* control_group_;
  Gtk::ToolItemGroup* misc_group_;

	Gtk::ScrolledWindow* canvas_window_;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITOR_H