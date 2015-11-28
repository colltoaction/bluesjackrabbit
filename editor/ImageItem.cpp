#include <goocanvasmm/image.h>
#include "EditorController.h"
#include "ImageItem.h"
// TODO(Diego): Borrar el include!
#include <iostream>

Glib::RefPtr<ImageItem> ImageItem::create(EditorController* controller,
    double x, double y) {
  return Glib::RefPtr<ImageItem>(new ImageItem(controller, x, y));
}

Glib::RefPtr<ImageItem> ImageItem::create(EditorController* controller,
    const Glib::RefPtr<Gdk::Pixbuf>& pixbuf, double x, double y) {
  Glib::RefPtr<ImageItem> item(new ImageItem(controller, pixbuf, x, y));
  item->signal_button_press_event().connect(
      sigc::mem_fun(*controller, &EditorController::prueba));
  return item;
}

ImageItem::ImageItem(EditorController* controller, double x, double y) : Goocanvas::Image(x, y),
    controller_(controller) {}

ImageItem::ImageItem(EditorController* controller, const Glib::RefPtr<Gdk::Pixbuf>& pixbuf,
    double x, double y) : Goocanvas::Image(pixbuf, x, y), controller_(controller) {
}
