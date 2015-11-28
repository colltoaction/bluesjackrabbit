#include <goocanvasmm/image.h>
#include "EditorCanvas.h"
#include "EditorController.h"
#include "ImageItem.h"
// TODO(Diego): Borrar el include!
#include <iostream>

Glib::RefPtr<ImageItem> ImageItem::create(EditorCanvas* canvas, EditorController* controller,
    double x, double y) {
  Glib::RefPtr<ImageItem> item(new ImageItem(controller, x, y));
  item->connect_signals(canvas);
  return item;
}
/*
Glib::RefPtr<ImageItem> ImageItem::create(EditorController* controller,
    const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y) {
  Glib::RefPtr<ImageItem> item(new ImageItem(controller, pixbuf, x, y));
  item->signal_button_press_event().connect(
      sigc::mem_fun(*(item->get_canvas()), &EditorCanvas::on_item_button_press));
  return item;
}
*/
Glib::RefPtr<ImageItem> ImageItem::create(EditorCanvas* canvas, EditorController* controller,
    const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y) {
  Glib::RefPtr<ImageItem> item(new ImageItem(controller, pixbuf, x, y));
  item->connect_signals(canvas);
  return item;
}

ImageItem::ImageItem(EditorController* controller, double x, double y) : Goocanvas::Image(x, y),
    controller_(controller) {}

ImageItem::ImageItem(EditorController* controller, const Glib::RefPtr<Gdk::Pixbuf>& pixbuf,
    double x, double y) : Goocanvas::Image(pixbuf, x, y), controller_(controller) {
}

void ImageItem::connect_signals(EditorCanvas* canvas) {
  signal_button_press_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_press));
  signal_button_release_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_release));
  signal_motion_notify_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_motion_notify));
}
