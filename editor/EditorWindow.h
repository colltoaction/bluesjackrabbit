#ifndef BLUESJACKRABBIT_EDITOR_EDITORWINDOW_H
#define BLUESJACKRABBIT_EDITOR_EDITORWINDOW_H

#include <gtkmm/entry.h>
#include <giomm/simpleactiongroup.h>
#include <giomm/simpleaction.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolitemgroup.h>
#include <gtkmm/toolpalette.h>
#include <gtkmm/window.h>
#include <goocanvasmm/canvas.h>
#include <goocanvasmm/item.h>
#include "EditorController.h"
#include "EditorCanvas.h"

class EditorWindow: public Gtk::Window {
 public:
  EditorWindow();
  virtual ~EditorWindow();

 private:
  /**
   * Loads the layout for this window from a Glade file
   */
  void load_content_from_glade();

  /**
   * Adds items from various assets to Editor's ToolPalette.
   */
  void init_palette();

  /**
   * Connects menu items to their corresponding Gio::SimpleAction
   */
  void init_menus();
  void change_layer(int parameter);

  Glib::RefPtr<Gtk::Builder> refBuilder_;
  EditorController controller_;

  Gtk::Box *root_;

  Gtk::ToolPalette *palette_;
  Gtk::ToolItemGroup *tiles_group_;
  Gtk::ToolItemGroup *control_group_;
  Gtk::ToolItemGroup *misc_group_;

  Gtk::ScrolledWindow *canvas_window_;
  EditorCanvas canvas_;

  Glib::RefPtr<Goocanvas::Item> dnd_item_;
  bool requested_for_motion_;
};

#endif  // BLUESJACKRABBIT_EDITOR_EDITORWINDOW_H
