#ifndef BLUESJACKRABBIT_EDITOR_IMAGEITEM_H
#define BLUESJACKRABBIT_EDITOR_IMAGEITEM_H
#include <map>
#include <goocanvasmm/image.h>
#include <goocanvasmm/bounds.h>
#include "EditorCanvas.h"
#include "LevelObject.h"

class ImageItem : public Goocanvas::Image {
 public:
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, EditorController* controller,
      double x, double y);
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, EditorController* controller,
      const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);
  virtual ~ImageItem() {}

 protected:
  ImageItem(EditorController* controller, double x, double y);
  ImageItem(EditorController* controller,
      const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);

 private:
  void connect_signals(EditorCanvas* canvas);

  // TODO(Diego) ver si no hace falta y se puede sacar
  EditorController* controller_;
};

#endif // BLUESJACKRABBIT_EDITOR_IMAGEITEM_H