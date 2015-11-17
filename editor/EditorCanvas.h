#ifndef BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
#define BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
#include <gtkmm/scrolledwindow.h>
#include <goocanvasmm/canvas.h>

class EditorCanvas : public Goocanvas::Canvas {
public:
  EditorCanvas(Gtk::ScrolledWindow*& parent);
  virtual ~EditorCanvas();

private:
  virtual void on_drag_data_received(
      const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
      const Gtk::SelectionData& selection_data, guint info, guint time);
  virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
      guint time);
  virtual bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
      guint time);
  Glib::RefPtr<Goocanvas::Item> create_canvas_item(double x, double y, Gtk::Widget* icon);

  Gtk::ScrolledWindow*& canvas_window_;
  Glib::RefPtr<Goocanvas::Item> dnd_item_;
  bool requested_for_motion_;

};

#endif // BLUESJACKRABBIT_EDITOR_EDITORCANVAS_H
