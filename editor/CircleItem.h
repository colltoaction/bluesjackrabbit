#ifndef BLUESJACKRABBIT_EDITOR_CIRCLEITEM_H
#define BLUESJACKRABBIT_EDITOR_CIRCLEITEM_H
#include <map>
#include <goocanvasmm/ellipse.h>
#include <goocanvasmm/bounds.h>
#include "EditorCanvas.h"
#include "LevelObject.h"

class CircleItem : public Goocanvas::Ellipse {
 public:
  static Glib::RefPtr<CircleItem> create(EditorCanvas* canvas, double x, double y,
      double radius);

  virtual ~CircleItem() {}

 protected:
  CircleItem(double x, double y, double radius);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_CIRCLEITEM_H