#ifndef BLUESJACKRABBIT_EDITOR_SPAWNPOINTITEM_H
#define BLUESJACKRABBIT_EDITOR_SPAWNPOINTITEM_H
#include <gtkmm/widget.h>
#include "ControlItem.h"
#include "EditorCanvas.h"

class SpawnPointItem : public ControlItem {
 public:
  static Glib::RefPtr<SpawnPointItem> create(EditorCanvas* canvas, Gtk::Widget* icon,
      double x, double y, double width, double height, bool moving, bool overlaps);
  virtual ~SpawnPointItem() {}
 protected:
  SpawnPointItem(Gtk::Widget* icon, double x, double y, double width, double height,
      bool moving, bool overlaps);
};

#endif // BLUESJACKRABBIT_EDITOR_SPAWNPOINTITEM_H