#ifndef BLUESJACKRABBIT_EDITOR_SPAWNPOINTITEM_H
#define BLUESJACKRABBIT_EDITOR_SPAWNPOINTITEM_H
#include <stdint.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "ControlItem.h"
#include "EditorCanvas.h"

class SpawnPointItem : public ControlItem, public CanvasItem {
 public:
  static Glib::RefPtr<SpawnPointItem> create(EditorCanvas* canvas, uint64_t id, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~SpawnPointItem() {}
 protected:
  SpawnPointItem(uint64_t id, Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);
};

#endif // BLUESJACKRABBIT_EDITOR_SPAWNPOINTITEM_H