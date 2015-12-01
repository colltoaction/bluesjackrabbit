#ifndef BLUESJACKRABBIT_EDITOR_STARTPOINTITEM_H
#define BLUESJACKRABBIT_EDITOR_STARTPOINTITEM_H
#include <gtkmm/widget.h>
#include "ControlItem.h"
#include "EditorCanvas.h"

class StartPointItem : public ControlItem {
 public:
  static Glib::RefPtr<StartPointItem> create(EditorCanvas* canvas, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~StartPointItem() {}
 protected:
  StartPointItem(Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);
};

#endif // BLUESJACKRABBIT_EDITOR_STARTPOINTITEM_H