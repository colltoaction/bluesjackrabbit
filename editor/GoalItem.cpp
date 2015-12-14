#include <stdint.h>
#include "CanvasItem.h"
#include "ControlItem.h"
#include "GoalItem.h"

Glib::RefPtr<GoalItem> GoalItem::create(EditorCanvas* canvas, uint64_t id, Gtk::Widget* icon,
    double x, double y, double width, double height, bool moving, bool overlaps) {
  Glib::RefPtr<GoalItem> item(new GoalItem(id, icon, x, y, width, height, moving, overlaps));
  ControlItem::setup(item, canvas);
  return item;
}

GoalItem::GoalItem(uint64_t id, Gtk::Widget* icon, double x, double y, double width,
    double height, bool moving, bool overlaps) :
    ControlItem(icon, x, y, width, height, moving, overlaps), CanvasItem(id) {
}
