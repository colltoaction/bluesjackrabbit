#include "ControlItem.h"
#include "StartPointItem.h"

Glib::RefPtr<StartPointItem> StartPointItem::create(EditorCanvas* canvas, Gtk::Widget* icon,
    double x, double y, double width, double height, bool moving, bool overlaps) {
  Glib::RefPtr<StartPointItem> item(
      new StartPointItem(icon, x, y, width, height, moving, overlaps));
  ControlItem::setup(item, canvas);
  return item;
}

StartPointItem::StartPointItem(Gtk::Widget* icon, double x, double y, double width, double height,
    bool moving, bool overlaps) : ControlItem(icon, x, y, width, height, moving, overlaps) {
}
