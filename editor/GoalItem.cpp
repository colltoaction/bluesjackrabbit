#include "ControlItem.h"
#include "GoalItem.h"

Glib::RefPtr<GoalItem> GoalItem::create(EditorCanvas* canvas, Gtk::Widget* icon,
    double x, double y, double width, double height, bool moving, bool overlaps) {
  Glib::RefPtr<GoalItem> item(
      new GoalItem(icon, x, y, width, height, moving, overlaps));
  ControlItem::setup(item, canvas);
  return item;
}

GoalItem::GoalItem(Gtk::Widget* icon, double x, double y, double width, double height,
    bool moving, bool overlaps) : ControlItem(icon, x, y, width, height, moving, overlaps) {
}
