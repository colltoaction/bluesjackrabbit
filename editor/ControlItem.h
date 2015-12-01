#ifndef BLUESJACKRABBIT_EDITOR_CONTROLITEM_H
#define BLUESJACKRABBIT_EDITOR_CONTROLITEM_H
#include <goocanvasmm/group.h>
#include <goocanvasmm/rect.h>
#include <gtkmm/widget.h>
#include "EditorCanvas.h"

class EditorCanvas;

class ControlItem : public Goocanvas::Group {
 public:
  static Glib::RefPtr<ControlItem> create(EditorCanvas* canvas, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~ControlItem() {}

  void update_box_style(bool moving, bool overlaps);

 protected:
  static void setup(Glib::RefPtr<ControlItem> control_item, EditorCanvas* canvas);
  ControlItem(Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);

 private:
  void connect_signals(EditorCanvas* canvas);

  Glib::RefPtr<Goocanvas::Rect> rect_;
};

#endif // BLUESJACKRABBIT_EDITOR_CONTROLITEM_H