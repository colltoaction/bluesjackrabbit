#include <stdint.h>
#include <goocanvasmm/ellipse.h>
#include "CanvasItem.h"
#include "EditorCanvas.h"
#include "EditorController.h"
#include "CircleItem.h"

Glib::RefPtr<CircleItem> CircleItem::create(EditorCanvas* canvas, uint64_t id,
    double x, double y, double radius) {
  Glib::RefPtr<CircleItem> item(new CircleItem(id, x, y, radius));
  item->set_property("fill_color", Glib::ustring("blue"));
  item->connect_signals(canvas);
  canvas->get_root_item()->add_child(item);
  return item;
}

CircleItem::CircleItem(uint64_t id, double x, double y, double radius) :
    Goocanvas::Ellipse(x, y, radius, radius), CanvasItem(id) {}

void CircleItem::connect_signals(EditorCanvas* canvas) {
  signal_button_press_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_press));
  signal_button_release_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_release));
  signal_motion_notify_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_motion_notify));
}
