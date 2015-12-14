#ifndef BLUESJACKRABBIT_EDITOR_BREAKABLERECTITEM_H
#define BLUESJACKRABBIT_EDITOR_BREAKABLERECTITEM_H
#include <map>
#include <stdint.h>
#include <goocanvasmm/rect.h>
#include <goocanvasmm/bounds.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "EditorCanvas.h"
#include "LevelObject.h"

class BreakableRectItem : public Goocanvas::Rect, public CanvasItem {
 public:
  static Glib::RefPtr<BreakableRectItem> create(EditorCanvas* canvas, uint64_t id, double x, double y,
      double width, double height);

  virtual ~BreakableRectItem() {}

 protected:
  BreakableRectItem(uint64_t id, double x, double y, double width, double height);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_BREAKABLERECTITEM_H