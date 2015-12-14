#ifndef BLUESJACKRABBIT_EDITOR_GOALITEM_H
#define BLUESJACKRABBIT_EDITOR_GOALITEM_H
#include <stdint.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "ControlItem.h"
#include "EditorCanvas.h"

class GoalItem : public ControlItem, public CanvasItem {
 public:
  static Glib::RefPtr<GoalItem> create(EditorCanvas* canvas, uint64_t id, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~GoalItem() {}
 protected:
  GoalItem(uint64_t id, Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);
};

#endif // BLUESJACKRABBIT_EDITOR_GOALITEM_H