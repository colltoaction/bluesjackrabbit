#include <goocanvasmm/image.h>
#include <gtkmm/image.h>
#include <gtkmm/widget.h>
#include "EditorCanvas.h"
#include "EditorController.h"
#include "RectItem.h"

Glib::RefPtr<RectItem> RectItem::create(EditorCanvas* canvas, double x, double y,
    double width, double height) {
  Glib::RefPtr<RectItem> item(new RectItem(x, y, width, height));
  item->set_property("fill_color", Glib::ustring("blue"));
  item->connect_signals(canvas);
  canvas->get_root_item()->add_child(item);
  return item;
}

RectItem::RectItem(double x, double y, double width, double height) :
    Goocanvas::Rect(x, y, width, height) {}

void RectItem::connect_signals(EditorCanvas* canvas) {
  signal_button_press_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_press));
  signal_button_release_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_release));
  signal_motion_notify_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_motion_notify));
}
