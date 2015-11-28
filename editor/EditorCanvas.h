#ifndef BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
#define BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H

#include <gtkmm/scrolledwindow.h>
#include <goocanvasmm/canvas.h>

typedef enum DraggableObjectType_ {
  /* Generic objects */
  GENERIC_IMAGE,
  RECTANGLE,
  CIRCLE,
  /* Control objects */
  START_POINT,
  SPAWN_POINT,
  GOAL
} DraggableObjectType;

class EditorCanvas : public Goocanvas::Canvas {
public:
  EditorCanvas(Gtk::ScrolledWindow*& parent, EditorController* controller);
  virtual ~EditorCanvas();

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

  Glib::RefPtr<Goocanvas::Item> create_canvas_item(double x, double y, Gtk::Widget* icon,
      DraggableObjectType obj_type);
  Glib::RefPtr<Goocanvas::Item> create_canvas_image(double x, double y, Gtk::Widget* icon);
  Glib::RefPtr<Goocanvas::Item> create_canvas_rect(double x, double y);
  Glib::RefPtr<Goocanvas::Item> create_canvas_circle(double x, double y);

  Gtk::ScrolledWindow*& canvas_window_;
  EditorController* controller_;
  Glib::RefPtr<Goocanvas::Item> dnd_item_;
  bool requested_for_motion_;

  // TODO(Diego)
  int n_borrar_es_para_pruebas;
};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
