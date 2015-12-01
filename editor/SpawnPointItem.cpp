#include "ControlItem.h"
#include "SpawnPointItem.h"

Glib::RefPtr<SpawnPointItem> SpawnPointItem::create(EditorCanvas* canvas, Gtk::Widget* icon,
    double x, double y, double width, double height, bool moving, bool overlaps) {
  Glib::RefPtr<SpawnPointItem> item(
      new SpawnPointItem(icon, x, y, width, height, moving, overlaps));
  ControlItem::setup(item, canvas);
  return item;
}

SpawnPointItem::SpawnPointItem(Gtk::Widget* icon, double x, double y, double width, double height,
    bool moving, bool overlaps) : ControlItem(icon, x, y, width, height, moving, overlaps) {
}
