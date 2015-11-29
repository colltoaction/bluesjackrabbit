#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolpalette.h>
#include <goocanvasmm/ellipse.h>
#include <goocanvasmm/rect.h>
#include "CircleButton.h"
#include "CircleItem.h"
#include "CircleLevelObject.h"
#include "EditorController.h"
#include "GenericImageLevelObject.h"
#include "ImageItem.h"
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "RectButton.h"
#include "RectangleLevelObject.h"
#include "RectItem.h"
#include "EditorCanvas.h"
#define LEFT_BUTTON 1
#define DEFAULT_RECT_WIDTH 64
#define DEFAULT_RECT_HEIGHT 32
#define DEFAULT_CIRCLE_RADIUS 32
#include <iostream>
#include <sstream>
#include <string>

EditorCanvas::EditorCanvas(Gtk::ScrolledWindow*& parent, EditorController* controller) :
    canvas_window_(parent), controller_(controller) {
}

EditorCanvas::~EditorCanvas() {}

void EditorCanvas::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
    int x, int y, const Gtk::SelectionData& selection_data, guint /* info */, guint timestamp) {
  /* The following chunk was taken from GNOME Developer's site - gtkmm ToolPalette Tutorial:
  https://developer.gnome.org/gtkmm-tutorial/stable/toolpalette-example.html.en
  in order to get the ToolItem which started the DnD operation */
  Gtk::Widget* widget = drag_get_source_widget(context);

  Gtk::ToolPalette* drag_palette = dynamic_cast<Gtk::ToolPalette*>(widget);
  while (widget && !drag_palette) {
    widget = widget->get_parent();
    drag_palette = dynamic_cast<Gtk::ToolPalette*>(widget);
  }

  Gtk::ToolItem* drag_item = 0;
  if (drag_palette) {
    drag_item = drag_palette->get_drag_item(selection_data);
  }

  Gtk::ToolButton* button = dynamic_cast<Gtk::ToolButton*>(drag_item);
  if (!button)
    return;

  LevelObjectType obj_type;
  Gtk::Widget* icon = NULL;
  if (dynamic_cast<RectButton*>(button)) {
    obj_type = RECTANGLE;
  } else if (dynamic_cast<CircleButton*>(button)) {
    obj_type = CIRCLE;
  } else {
    obj_type = GENERIC_IMAGE;
    icon = button->get_icon_widget();
  }

  /* This method is called from either drag_motion or drag_drop, and the DragContext has to be
  updated in consequence */
  if (requested_for_motion_) {
    if (!item_being_moved_) {
      item_being_moved_ = create_canvas_item(x, y, icon, obj_type);
    }
    context->drag_status(Gdk::ACTION_COPY, timestamp);
    requested_for_motion_ = false;
  } else {
    item_being_moved_->remove();
    item_being_moved_.reset();

    LevelObject* object = NULL;
    Glib::RefPtr<Goocanvas::Item> obj_representation;
    double item_x = x;
    double item_y = y;
    convert_to_canvas_coordinates(item_x, item_y);

    switch (obj_type) {
    case CIRCLE:
      obj_representation = CircleItem::create(this, item_x, item_y, DEFAULT_CIRCLE_RADIUS);
      object = new CircleLevelObject(item_x, item_y, DEFAULT_CIRCLE_RADIUS, obj_representation);
      controller_->register_object(object);
      break;
    case RECTANGLE:
      obj_representation = RectItem::create(this, item_x, item_y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
      object = new RectangleLevelObject(item_x, item_y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT,
          obj_representation);
      controller_->register_object(object);
      break;
    case GENERIC_IMAGE:
      obj_representation = ImageItem::create(this, icon, item_x, item_y);
      object = new GenericImageLevelObject(item_x, item_y, obj_representation);
      controller_->register_object(object);
      break;
    default:
      break;
    }
    context->drag_finish(false, false, timestamp);
  }
}

bool EditorCanvas::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
    guint timestamp) {
  /* Look for a match between source and destination TargetEntries */
  const Glib::ustring target = drag_dest_find_target(context);
  if (target.empty()) {
    return false;
  }

  drag_highlight();

  /* If item exists, we're supposed to move it and call drag_status() */
  if (item_being_moved_) {
    move_item(item_being_moved_, x, y);
    context->drag_status(Gdk::ACTION_COPY, timestamp);
  } else {
    /* If item doesn't exist, we should get it's data from the source and create it. It's achieved
    via the drag_get_data method, which in turn emits the drag_data_received signal */
    requested_for_motion_ = true;
    drag_get_data(context, target, timestamp);
  }

  return true;
}

bool EditorCanvas::on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context,
    int /* x */, int /* y */, guint timestamp) {
  const Glib::ustring target = drag_dest_find_target(context);
  if (target.empty()) {
    return false;
  }
  drag_get_data(context, target, timestamp);
  return true;
}

void EditorCanvas::convert_to_canvas_coordinates(double &x, double &y) {
  x += canvas_window_->get_hadjustment()->get_value();
  y += canvas_window_->get_vadjustment()->get_value();
  convert_from_pixels(x, y);
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_item(double x, double y,
    Gtk::Widget* icon, LevelObjectType obj_type) {
  double item_x = x;
  double item_y = y;
  convert_to_canvas_coordinates(item_x, item_y);

  Glib::RefPtr<Goocanvas::Item> canvas_item;
  switch (obj_type) {
  case CIRCLE:
    canvas_item = create_canvas_circle(item_x, item_y);
    break;
  case RECTANGLE:
    canvas_item = create_canvas_rect(item_x, item_y);
    break;
  case GENERIC_IMAGE:
  default:
    canvas_item = create_canvas_image(item_x, item_y, icon);
    break;
  }
  return canvas_item;
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_image(double x, double y,
    Gtk::Widget* icon) {
  return ImageItem::create(this, icon, x, y);
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_rect(double x, double y) {
  return RectItem::create(this, x, y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_circle(double x, double y) {
  return CircleItem::create(this, x, y, DEFAULT_CIRCLE_RADIUS);
}

void EditorCanvas::move_item(Glib::RefPtr<Goocanvas::Item> item, gdouble x, gdouble y) {
  gdouble t_x, t_y, t_scale, t_rotation;
  item->get_simple_transform(t_x, t_y, t_scale, t_rotation);
  item->translate(x - t_x, y - t_y);
  // controller_->update_object(item, )
}

bool EditorCanvas::on_item_button_press(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventButton* event) {
  if (event->type == GDK_BUTTON_PRESS) {
    selected_items_.clear();
    selected_items_.push_back(item);
    if (event->button == LEFT_BUTTON) {
      item_being_moved_ = item;
      original_x_ = event->x;
      original_y_ = event->y;
      convert_from_pixels(original_x_, original_y_);
    }
  }
  return true;
}

bool EditorCanvas::on_item_button_release(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventButton* event) {
  if (event->button == LEFT_BUTTON && item_being_moved_ == item) {
    item_being_moved_.reset();
  }
  return true;
}

bool EditorCanvas::on_item_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventMotion* event) {
  gdouble item_x = event->x;
  gdouble item_y = event->y;
  convert_from_pixels(item_x, item_y);
  if (item == item_being_moved_) {
    gdouble delta_x = item_x - original_x_;
    gdouble delta_y = item_y - original_y_;
    gdouble t_x, t_y, t_scale, t_rotation;
    item->get_simple_transform(t_x, t_y, t_scale, t_rotation);
    move_item(item, t_x + delta_x, t_y + delta_y);
  }
  return true;
}
