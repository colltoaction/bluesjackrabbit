#ifndef BLUESJACKRABBIT_EDITOR_CIRCLEITEM_H
#define BLUESJACKRABBIT_EDITOR_CIRCLEITEM_H
#include <map>
#include <stdint.h>
#include <goocanvasmm/ellipse.h>
#include <goocanvasmm/bounds.h>
#include "CanvasItem.h"
#include "EditorCanvas.h"
#include "LevelObject.h"

class CircleItem : public Goocanvas::Ellipse, public CanvasItem {
 public:
  static Glib::RefPtr<CircleItem> create(EditorCanvas* canvas,  uint64_t id,
    double x, double y, double radius);

  virtual ~CircleItem() {}

 protected:
  CircleItem(uint64_t id, double x, double y, double radius);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_CIRCLEITEM_H