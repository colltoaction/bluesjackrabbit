#ifndef BLUESJACKRABBIT_EDITOR_IMAGEITEM_H
#define BLUESJACKRABBIT_EDITOR_IMAGEITEM_H
#include <stdint.h>
#include <goocanvasmm/image.h>
#include <goocanvasmm/bounds.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "EditorCanvas.h"

class ImageItem : public Goocanvas::Image, public CanvasItem {
 public:
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, uint64_t id,
      double x, double y);
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, uint64_t id,
      const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, uint64_t id,
      Gtk::Widget* icon, double x, double y);

  virtual ~ImageItem() {}

 protected:
  ImageItem(uint64_t id, double x, double y);
  ImageItem(uint64_t id, const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_IMAGEITEM_H