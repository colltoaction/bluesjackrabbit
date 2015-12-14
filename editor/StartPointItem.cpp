#include "CanvasItem.h"
#include "ControlItem.h"
#include "StartPointItem.h"

Glib::RefPtr<StartPointItem> StartPointItem::create(EditorCanvas* canvas, uint64_t id,
    Gtk::Widget* icon,
    double x, double y, double width, double height, bool moving, bool overlaps) {
  Glib::RefPtr<StartPointItem> item(
      new StartPointItem(id, icon, x, y, width, height, moving, overlaps));
  ControlItem::setup(item, canvas);
  return item;
}

StartPointItem::StartPointItem(uint64_t id, Gtk::Widget* icon, double x, double y, double width,
    double height,
    bool moving, bool overlaps) : ControlItem(icon, x, y, width, height, moving, overlaps),
    CanvasItem(id) {
}
