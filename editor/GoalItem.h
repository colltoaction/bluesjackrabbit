#ifndef BLUESJACKRABBIT_EDITOR_GOALITEM_H
#define BLUESJACKRABBIT_EDITOR_GOALITEM_H
#include <gtkmm/widget.h>
#include "ControlItem.h"
#include "EditorCanvas.h"

class GoalItem : public ControlItem {
 public:
  static Glib::RefPtr<GoalItem> create(EditorCanvas* canvas, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~GoalItem() {}
 protected:
  GoalItem(Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);
};

#endif // BLUESJACKRABBIT_EDITOR_GOALITEM_H