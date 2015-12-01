#include <goocanvasmm/group.h>
#include <goocanvasmm/image.h>
#include <goocanvasmm/rect.h>
#include <gtkmm/image.h>
#include <gtkmm/widget.h>
#include "EditorCanvas.h"
#include "ControlItem.h"
#define LIGHT_BLUE 0x86CCE350
#define LIGHT_GREEN 0x96DE7E50
#define LIGHT_RED 0xED535150

Glib::RefPtr<ControlItem> ControlItem::create(EditorCanvas* canvas, Gtk::Widget* icon,
    double x, double y, double width, double height, bool moving, bool overlaps) {
  Glib::RefPtr<ControlItem> item(
      new ControlItem(icon, x, y, width, height, moving, overlaps));
  item->connect_signals(canvas);
  canvas->get_root_item()->add_child(item);
  return item;
}

void ControlItem::setup(Glib::RefPtr<ControlItem> control_item, EditorCanvas* canvas) {
  control_item->connect_signals(canvas);
  canvas->get_root_item()->add_child(control_item);
}

ControlItem::ControlItem(Gtk::Widget* icon, double x, double y, double width,
    double height, bool moving, bool overlaps) {
  rect_ = Goocanvas::Rect::create(x, y, width, height);
  if (moving) {
    rect_->set_property("fill_color_rgba", LIGHT_BLUE);
  } else if (overlaps) {
    rect_->set_property("fill_color_rgba", LIGHT_RED);
  } else {
    rect_->set_property("fill_color_rgba", LIGHT_GREEN);
  }

  add_child(rect_);
  Gtk::Image* image = dynamic_cast<Gtk::Image*>(icon);
  Glib::RefPtr<Goocanvas::Image> item = Goocanvas::Image::create(image->get_pixbuf(), x, y);
  add_child(item);
}

void ControlItem::connect_signals(EditorCanvas* canvas) {
  signal_button_press_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_group_button_press));
  signal_button_release_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_group_button_release));
  signal_motion_notify_event().connect(
      sigc::mem_fun(canvas, &EditorCanvas::on_group_motion_notify));
}

void ControlItem::update_box_style(bool moving, bool overlaps) {
    if (moving) {
    rect_->set_property("fill_color_rgba", LIGHT_BLUE);
  } else if (overlaps) {
    rect_->set_property("fill_color_rgba", LIGHT_RED);
  } else {
    rect_->set_property("fill_color_rgba", LIGHT_GREEN);
  }
}
