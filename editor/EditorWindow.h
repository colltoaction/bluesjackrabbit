#ifndef BLUESJACKRABBIT_EDITOR_EDITORWINDOW_H
#define BLUESJACKRABBIT_EDITOR_EDITORWINDOW_H
#include <giomm/simpleactiongroup.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolitemgroup.h>
#include <gtkmm/toolpalette.h>
#include <gtkmm/window.h>
#include <goocanvasmm/canvas.h>
#include "EditorController.h"
#include "EditorCanvas.h"
// #include "Level.h"

class EditorWindow : public Gtk::Window {
 public:
	EditorWindow();
	virtual ~EditorWindow();
  /**
   * Handles Canvas's on_drag_motion signal. It's signature matches the standard slot for
   * that signal.
   */
  bool on_canvas_drag_motion(
      const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp);
  /**
   * Handles Canvas's on_drag_drop signal. It's signature matches the standard slot for
   * that signal.
   */
  bool on_canvas_drag_drop(
      const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp);
  /**
   * Handles Canvas's on_drag_data_received signal. It's signature matches the standard slot for
   * that signal.
   */
  void on_canvas_drag_data_received(
      const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, 
      const Gtk::SelectionData& selection_data, guint info, guint timestamp);
  void on_palette_drag_data_get(
      const Glib::RefPtr<Gdk::DragContext>& /* drag_context */, Gtk::SelectionData& selection_data,
      guint /* info */, guint /* time */);
  void on_toolbutton_drag_data_get(
      const Glib::RefPtr<Gdk::DragContext>& /* drag_context */, Gtk::SelectionData& selection_data,
      guint /* info */, guint /* time */, std::string asset_uid);


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
  void tilemap_visible();

  Glib::RefPtr<Goocanvas::Item> create_canvas_item(double x, double y);
  Glib::RefPtr<Goocanvas::Item> create_canvas_item(double x, double y, Gtk::Widget* icon);

  EditorController controller_;

	Gtk::Box* root_;
	
	Gtk::ToolPalette* palette_;
  Gtk::ToolItemGroup* tiles_group_;
  Gtk::ToolItemGroup* control_group_;
  Gtk::ToolItemGroup* misc_group_;

  Gtk::ScrolledWindow* canvas_window_;
  EditorCanvas canvas_;

  Glib::RefPtr<Goocanvas::Item> dnd_item_;
  bool requested_for_motion_;

  Glib::RefPtr<Gio::SimpleAction> action_active_layer_;
  Glib::RefPtr<Gio::SimpleAction> action_tilemap_visible_;
  Glib::RefPtr<Gio::SimpleAction> action_objects_visible_;
  Glib::RefPtr<Gio::SimpleAction> action_controls_visible_;

};

#endif // BLUESJACKRABBIT_EDITOR_EDITORWINDOW_H