#include <goocanvasmm/image.h>
#include <gtkmm/image.h>
#include <gtkmm/widget.h>
#include "EditorCanvas.h"
#include "EditorController.h"
#include "ImageItem.h"
// TODO(Diego): Borrar el include!
#include <iostream>

Glib::RefPtr<ImageItem> ImageItem::create(EditorCanvas* canvas, double x, double y) {
  Glib::RefPtr<ImageItem> item(new ImageItem(x, y));
  item->connect_signals(canvas);
  canvas->get_root_item()->add_child(item);
  return item;
}

Glib::RefPtr<ImageItem> ImageItem::create(EditorCanvas* canvas,
    const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y) {
  Glib::RefPtr<ImageItem> item(new ImageItem(pixbuf, x, y));
  item->connect_signals(canvas);
  canvas->get_root_item()->add_child(item);
  return item;
}

Glib::RefPtr<ImageItem> ImageItem::create(EditorCanvas* canvas,
    Gtk::Widget* icon, double x, double y) {
  Gtk::Image* image = dynamic_cast<Gtk::Image*>(icon);
  return create(canvas, image->get_pixbuf(), x, y);
}

ImageItem::ImageItem(double x, double y) : Goocanvas::Image(x, y) {}

ImageItem::ImageItem(const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y) :
    Goocanvas::Image(pixbuf, x, y) {
}

void ImageItem::connect_signals(EditorCanvas* canvas) {
  signal_button_press_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_press));
  signal_button_release_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_release));
  signal_motion_notify_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_motion_notify));
}
