#ifndef BLUESJACKRABBIT_EDITOR_RECTITEM_H
#define BLUESJACKRABBIT_EDITOR_RECTITEM_H
#include <map>
#include <stdint.h>
#include <goocanvasmm/rect.h>
#include <goocanvasmm/bounds.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "EditorCanvas.h"
#include "LevelObject.h"

class RectItem : public Goocanvas::Rect, public CanvasItem {
 public:
  static Glib::RefPtr<RectItem> create(EditorCanvas* canvas, uint64_t id, double x, double y,
      double width, double height);

  virtual ~RectItem() {}

 protected:
  RectItem(uint64_t id, double x, double y, double width, double height);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_RECTITEM_H