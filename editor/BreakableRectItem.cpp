#include <goocanvasmm/image.h>
#include <gtkmm/image.h>
#include <gtkmm/widget.h>
#include "CanvasItem.h"
#include "EditorCanvas.h"
#include "EditorController.h"
#include "BreakableRectItem.h"

Glib::RefPtr<BreakableRectItem> BreakableRectItem::create(EditorCanvas* canvas, uint64_t id, double x, double y,
    double width, double height) {
  Glib::RefPtr<BreakableRectItem> item(new BreakableRectItem(id, x, y, width, height));
  item->set_property("fill_color", Glib::ustring("red"));
  item->connect_signals(canvas);
  canvas->get_root_item()->add_child(item);
  return item;
}

BreakableRectItem::BreakableRectItem(uint64_t id, double x, double y, double width, double height) :
    Goocanvas::Rect(x, y, width, height), CanvasItem(id) {}

void BreakableRectItem::connect_signals(EditorCanvas* canvas) {
  signal_button_press_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_press));
  signal_button_release_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_button_release));
  signal_motion_notify_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_item_motion_notify));
}
