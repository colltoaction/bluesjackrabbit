#ifndef BLUESJACKRABBIT_EDITOR_IMAGEITEM_H
#define BLUESJACKRABBIT_EDITOR_IMAGEITEM_H
#include <map>
#include <goocanvasmm/image.h>
#include <goocanvasmm/bounds.h>
#include <gtkmm/widget.h>
#include "EditorCanvas.h"

class ImageItem : public Goocanvas::Image {
 public:
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, double x, double y);
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas,
      const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);
  static Glib::RefPtr<ImageItem> create(EditorCanvas* canvas, Gtk::Widget* icon,
      double x, double y);

  virtual ~ImageItem() {}

 protected:
  ImageItem(double x, double y);
  ImageItem(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y);

 private:
  void connect_signals(EditorCanvas* canvas);
};

#endif // BLUESJACKRABBIT_EDITOR_IMAGEITEM_H