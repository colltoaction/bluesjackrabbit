#ifndef BLUESJACKRABBIT_EDITOR_RECTITEM_H
#define BLUESJACKRABBIT_EDITOR_RECTITEM_H
#include <map>
#include <goocanvasmm/rect.h>
#include <goocanvasmm/bounds.h>
#include <gtkmm/widget.h>
#include "EditorCanvas.h"
#include "LevelObject.h"

class RectItem : public Goocanvas::Rect {
 public:
  static Glib::RefPtr<RectItem> create(EditorCanvas* canvas, double x, double y,
      double width, double height);

  virtual ~RectItem() {}

 protected:
  RectItem(double x, double y, double width, double height);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_RECTITEM_H