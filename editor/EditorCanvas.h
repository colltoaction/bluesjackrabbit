#ifndef BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
#define BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
#include <vector>
#include <stdint.h>
#include <gtkmm/scrolledwindow.h>
#include <goocanvasmm/canvas.h>
#include <goocanvasmm/group.h>
#include "ControlItem.h"
#include "LevelObjectType.h"
#include "EditorController.h"

class EditorCanvas : public Goocanvas::Canvas {
public:
  EditorCanvas(Gtk::ScrolledWindow*& parent, EditorController* controller);
  virtual ~EditorCanvas();
  bool on_item_button_press(const Glib::RefPtr<Goocanvas::Item>& item,
      GdkEventButton* event);
  bool on_item_button_release(const Glib::RefPtr<Goocanvas::Item>& item,
      GdkEventButton* event);
  bool on_item_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item,
      GdkEventMotion* event);
  bool on_group_button_press(const Glib::RefPtr<Goocanvas::Item>& item,
      GdkEventButton* event);
  bool on_group_button_release(const Glib::RefPtr<Goocanvas::Item>& item,
      GdkEventButton* event);
  bool on_group_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item,
      GdkEventMotion* event);
  void clear_canvas(const Glib::VariantBase& /* parameter */);

private:
  /**
   * Handles Canvas's on_drag_data_received signal. It's signature matches the standard slot for
   * that signal.
   */  
  virtual void on_drag_data_received(
      const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
      const Gtk::SelectionData& selection_data, guint info, guint time);
  /**
   * Handles Canvas's on_drag_motion signal. It's signature matches the standard slot for
   * that signal.
   */
  virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
      guint time);
  /**
   * Handles Canvas's on_drag_drop signal. It's signature matches the standard slot for
   * that signal.
   */
  virtual bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
      guint time);

  uint64_t next_item_id();
  void convert_to_canvas_coordinates(double &x, double &y);
  Glib::RefPtr<Goocanvas::Item> create_canvas_item(double x, double y, Gtk::Widget* icon,
      LevelObjectType obj_type);
  Glib::RefPtr<Goocanvas::Item> create_canvas_image(double x, double y, Gtk::Widget* icon);
  Glib::RefPtr<Goocanvas::Item> create_canvas_break_rect(double x, double y);
  Glib::RefPtr<Goocanvas::Item> create_canvas_rect(double x, double y);
  Glib::RefPtr<Goocanvas::Item> create_canvas_circle(double x, double y);
  void move_item(Glib::RefPtr<Goocanvas::Item> item, gdouble x, gdouble y);
  Glib::RefPtr<Goocanvas::Group> get_group(const Glib::RefPtr<Goocanvas::Item>& item);
  bool is_overlapped(Glib::RefPtr<Goocanvas::Item> item);
  uint64_t get_item_id(const Glib::RefPtr<Goocanvas::Item>& item);

  Gtk::ScrolledWindow*& canvas_window_;
  EditorController* controller_;
  
  uint64_t item_counter_;
  Glib::RefPtr<Goocanvas::Item> item_being_moved_;
  std::vector<Glib::RefPtr<Goocanvas::Item> > selected_items_;
  bool requested_for_motion_;
  gdouble original_abs_x_;
  gdouble original_abs_y_;
  gdouble original_rel_ev_x_;
  gdouble original_rel_ev_y_;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
