#include <string>
#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolpalette.h>
#include <goocanvasmm/group.h>
#include <goocanvasmm/ellipse.h>
#include <goocanvasmm/rect.h>
#include "BreakableRectButton.h"
#include "BreakableRectItem.h"
#include "CanvasItem.h"
#include "CircleButton.h"
#include "CircleItem.h"
#include "CircleLevelObject.h"
#include "ControlItem.h"
#include "EditorController.h"
#include "GenericImageLevelObject.h"
#include "GoalButton.h"
#include "GoalItem.h"
#include "GoalLevelObject.h"
#include "ImageItem.h"
#include "LevelObject.h"
#include "LevelObjectType.h"
#include "RectButton.h"
#include "RectangleLevelObject.h"
#include "RectItem.h"
#include "SpawnPointButton.h"
#include "SpawnPointItem.h"
#include "SpawnPointLevelObject.h"
#include "StartPointButton.h"
#include "StartPointItem.h"
#include "StartPointLevelObject.h"
#include "EditorCanvas.h"
#define LEFT_BUTTON 1
#define DEFAULT_RECT_WIDTH 64
#define DEFAULT_RECT_HEIGHT 32
#define DEFAULT_CIRCLE_RADIUS 32
#define DEFAULT_CONTROL_HEIGHT 64
#include <iostream>
#include <sstream>
#include <string>

EditorCanvas::EditorCanvas(Gtk::ScrolledWindow*& parent, EditorController* controller) :
    canvas_window_(parent), controller_(controller), item_counter_(1) {
}

EditorCanvas::~EditorCanvas() {}

uint64_t EditorCanvas::next_item_id() {
  return item_counter_++;
}

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
  std::string file;
  if (dynamic_cast<RectButton*>(button)) {
    obj_type = RECTANGLE;
  } else if (dynamic_cast<BreakableRectButton*>(button)) {
    obj_type = BREAKABLE_RECT;
  } else if (dynamic_cast<CircleButton*>(button)) {
    obj_type = CIRCLE;
  } else {
    icon = button->get_icon_widget();
    if (dynamic_cast<SpawnPointButton*>(button)) {
      obj_type = SPAWN_POINT;
    } else if (dynamic_cast<StartPointButton*>(button)) {
      obj_type = START_POINT;
    } else if (dynamic_cast<GoalButton*>(button)) {
      obj_type = GOAL;
    } else {
      obj_type = GENERIC_IMAGE;
      file = button->get_label();
    }
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
    // Glib::RefPtr<Goocanvas::Item> obj_representation;
    double item_x = x;
    double item_y = y;
    convert_to_canvas_coordinates(item_x, item_y);

    switch (obj_type) {
    case CIRCLE:
      {
        Glib::RefPtr<CircleItem> obj_representation = CircleItem::create(
            this, next_item_id(), item_x, item_y, DEFAULT_CIRCLE_RADIUS);
        CanvasItem& canvas_obj = obj_representation->dereference();
        object = new CircleLevelObject(item_x, item_y, DEFAULT_CIRCLE_RADIUS, canvas_obj);
        break;
      }
    case BREAKABLE_RECT:
      {
        item_x = static_cast<int>(item_x) / 32 * 32;
        item_y = static_cast<int>(item_y) / 32 * 32;
        Glib::RefPtr<BreakableRectItem> obj_representation = BreakableRectItem::create(this,
            next_item_id(), item_x, item_y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
        object = new RectangleLevelObject(item_x, item_y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT,
            obj_representation->dereference(), true);
        break;
      }
    case RECTANGLE:
      {
        item_x = static_cast<int>(item_x) / 32 * 32;
        item_y = static_cast<int>(item_y) / 32 * 32;
        Glib::RefPtr<RectItem> obj_representation = RectItem::create(this, next_item_id(), item_x,
            item_y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
        object = new RectangleLevelObject(item_x, item_y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT,
            obj_representation->dereference(), false);
        break;
      }
    case SPAWN_POINT:
      {
        Glib::RefPtr<SpawnPointItem> spawn_point = SpawnPointItem::create(this,
            next_item_id(), icon, x, y,
            DEFAULT_CONTROL_HEIGHT, DEFAULT_CONTROL_HEIGHT, false, true);
        spawn_point->update_box_style(false, is_overlapped(spawn_point));
        object = new SpawnPointLevelObject(item_x, item_y, spawn_point->dereference());
      }
      break;
    case START_POINT:
      {
        Glib::RefPtr<StartPointItem> start_point = StartPointItem::create(this,
            next_item_id(), icon, x, y,
            DEFAULT_CONTROL_HEIGHT, DEFAULT_CONTROL_HEIGHT, false, true);
        start_point->update_box_style(false, is_overlapped(start_point));
        object = new StartPointLevelObject(item_x, item_y, start_point->dereference());
      }
      break;
    case GOAL:
      {
        Glib::RefPtr<GoalItem> goal = GoalItem::create(this, next_item_id(),
            icon, x, y, DEFAULT_CONTROL_HEIGHT,
            DEFAULT_CONTROL_HEIGHT, false, true);
        goal->update_box_style(false, is_overlapped(goal));
        object = new GoalLevelObject(item_x, item_y, goal->dereference());
      }
      break;
    case GENERIC_IMAGE:
      {
        Glib::RefPtr<ImageItem> obj_representation = ImageItem::create(this, next_item_id(), icon,
            item_x, item_y);
        object = new GenericImageLevelObject(file, item_x, item_y,
            obj_representation->dereference());
        break;
      }
    default:
      break;
    }
    controller_->register_object(object);
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
  case BREAKABLE_RECT:
    canvas_item = create_canvas_break_rect(item_x, item_y);
    break;
  case RECTANGLE:
    canvas_item = create_canvas_rect(item_x, item_y);
    break;
  case SPAWN_POINT:
    canvas_item = SpawnPointItem::create(this, 0, icon, x, y, DEFAULT_CONTROL_HEIGHT,
        DEFAULT_CONTROL_HEIGHT, true, false);
    break;
  case START_POINT:
    canvas_item = StartPointItem::create(this, 0, icon, x, y, DEFAULT_CONTROL_HEIGHT,
        DEFAULT_CONTROL_HEIGHT, true, false);
    break;
  case GOAL:
    canvas_item = GoalItem::create(this, 0, icon, x, y, DEFAULT_CONTROL_HEIGHT,
        DEFAULT_CONTROL_HEIGHT, true, false);
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
  return ImageItem::create(this, 0, icon, x, y);
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_rect(double x, double y) {
  return RectItem::create(this, 0, x, y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_break_rect(double x, double y) {
  return BreakableRectItem::create(this, 0, x, y, DEFAULT_RECT_WIDTH, DEFAULT_RECT_HEIGHT);
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_circle(double x, double y) {
  return CircleItem::create(this, 0, x, y, DEFAULT_CIRCLE_RADIUS);
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
      convert_to_canvas_coordinates(original_x_, original_y_);
      // convert_from_pixels(original_x_, original_y_);
    }
  }
  return true;
}

bool EditorCanvas::on_item_button_release(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventButton* event) {
  if (event->button == LEFT_BUTTON && item_being_moved_ == item) {
    LevelObject* obj = controller_->get_registered_object(get_item_id(item));
    double item_x = item->property_x().get_value();
    double item_y = item->property_y().get_value();
    convert_from_item_space(item, item_x, item_y);
    item_x = static_cast<int>(item_x + canvas_window_->get_hadjustment()->get_value()) / 32 * 32;
    item_y = static_cast<int>(item_y + canvas_window_->get_vadjustment()->get_value()) / 32 * 32;
    obj->set_x(item_x);
    obj->set_y(item_y);
    convert_to_item_space(item, item_x, item_y);
    item->property_x().set_value(item_x);
    item->property_y().set_value(item_y);

    item_being_moved_.reset();
  }
  return true;
}

// El metodo mejor programado del universo
uint64_t EditorCanvas::get_item_id(const Glib::RefPtr<Goocanvas::Item>& item) {
  Glib::RefPtr<CircleItem> circle_ptr = Glib::RefPtr<CircleItem>::cast_dynamic(item);
  if (circle_ptr) {
    return circle_ptr->item_id();
  }
  Glib::RefPtr<BreakableRectItem> break_rect_ptr =
      Glib::RefPtr<BreakableRectItem>::cast_dynamic(item);
  if (break_rect_ptr) {
    return break_rect_ptr->item_id();
  }
  Glib::RefPtr<RectItem> rect_ptr = Glib::RefPtr<RectItem>::cast_dynamic(item);
  if (rect_ptr) {
    return rect_ptr->item_id();
  }
  Glib::RefPtr<ImageItem> image_ptr = Glib::RefPtr<ImageItem>::cast_dynamic(item);
  if (image_ptr) {
    return image_ptr->item_id();
  }
  Glib::RefPtr<GoalItem> goal_ptr = Glib::RefPtr<GoalItem>::cast_dynamic(item);
  if (goal_ptr) {
    return goal_ptr->item_id();
  }
  Glib::RefPtr<SpawnPointItem> spawn_ptr = Glib::RefPtr<SpawnPointItem>::cast_dynamic(item);
  if (spawn_ptr) {
    return spawn_ptr->item_id();
  }
  Glib::RefPtr<StartPointItem> start_ptr = Glib::RefPtr<StartPointItem>::cast_dynamic(item);
  if (start_ptr) {
    return start_ptr->item_id();
  }
  std::cout << "Assert: el item seleccionado no se puede castear a ninguno de los"
    "tipos reconocidos por get_item_id()" << std::endl;
  return 0;
}

bool EditorCanvas::on_item_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventMotion* event) {
  gdouble item_x = event->x;
  gdouble item_y = event->y;
  convert_to_canvas_coordinates(item_x, item_y);
  if (item == item_being_moved_) {
    gdouble delta_x = item_x - original_x_;
    gdouble delta_y = item_y - original_y_;
    gdouble t_x, t_y, t_scale, t_rotation;
    item->get_simple_transform(t_x, t_y, t_scale, t_rotation);
    move_item(item, t_x + delta_x, t_y + delta_y);
  }
  return true;
}

Glib::RefPtr<Goocanvas::Group> EditorCanvas::get_group(const Glib::RefPtr<Goocanvas::Item>& item) {
  Glib::RefPtr<Goocanvas::Group> items_group = Glib::RefPtr<Goocanvas::Group>::cast_dynamic(item);
  if (!items_group) {
    items_group = Glib::RefPtr<Goocanvas::Group>::cast_dynamic(item->get_parent());
  }
  return items_group;
}

bool EditorCanvas::on_group_button_press(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventButton* event) {
  return on_item_button_press(get_group(item), event);
}

bool EditorCanvas::on_group_button_release(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventButton* event) {
  Glib::RefPtr<ControlItem> control_item =
      Glib::RefPtr<ControlItem>::cast_dynamic(get_group(item));
  control_item->update_box_style(false, is_overlapped(control_item));
  return on_item_button_release(control_item, event);
}

bool EditorCanvas::on_group_motion_notify(const Glib::RefPtr<Goocanvas::Item>& item,
    GdkEventMotion* event) {
  return on_item_motion_notify(get_group(item), event);
}

bool EditorCanvas::is_overlapped(Glib::RefPtr<Goocanvas::Item> item) {
  std::vector< Glib::RefPtr<Goocanvas::Item> > items_overlapped =
      get_items_in_area(item->get_bounds(), true, true, false);
  std::vector< Glib::RefPtr<Goocanvas::Item> >::iterator it = items_overlapped.begin();
  while (it != items_overlapped.end()) {
    if (item != *it && item->find_child(*it) < 0)
      return true;
    ++it;
  }
  return false;
}

void EditorCanvas::clear_canvas(const Glib::VariantBase& /* parameter */) {
  std::cout << "Limpiando canvas" << std::endl;
  int cant_items = get_root_item()->get_n_children();
  for (int i = 0; i < cant_items; i++) {
    get_root_item()->get_child(0)->remove();
  }
}
