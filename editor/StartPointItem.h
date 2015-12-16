#ifndef BLUESJACKRABBIT_EDITOR_STARTPOINTITEM_H
#define BLUESJACKRABBIT_EDITOR_STARTPOINTITEM_H
#include <stdint.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "ControlItem.h"
#include "EditorCanvas.h"

class StartPointItem : public ControlItem, public CanvasItem {
 public:
  static Glib::RefPtr<StartPointItem> create(EditorCanvas* canvas, uint64_t id, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~StartPointItem() {}
 protected:
  StartPointItem(uint64_t id, Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);
};

#endif // BLUESJACKRABBIT_EDITOR_STARTPOINTITEM_H