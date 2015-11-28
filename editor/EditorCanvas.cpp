#include <gtkmm/image.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolpalette.h>
#include <goocanvasmm/ellipse.h>
#include <goocanvasmm/rect.h>
#include "CircleButton.h"
#include "EditorController.h"
#include "ImageItem.h"
#include "RectButton.h"
#include "EditorCanvas.h"

#include <iostream>
#include <sstream>
#include <string>

EditorCanvas::EditorCanvas(Gtk::ScrolledWindow*& parent, EditorController* controller) :
    canvas_window_(parent), controller_(controller) {
  std::cout << parent << std::endl;
}

EditorCanvas::~EditorCanvas() {}

void EditorCanvas::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
    int x, int y, const Gtk::SelectionData& selection_data, guint /* info */, guint timestamp) {
    std::cout << selection_data.get_length() << std::endl;

  double item_x = x + canvas_window_->get_hadjustment()->get_value();
  double item_y = y + canvas_window_->get_vadjustment()->get_value();
  convert_from_pixels(item_x, item_y);

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

  DraggableObjectType obj_type;
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
    if (!dnd_item_) {
      dnd_item_ = create_canvas_item(item_x, item_y, icon, obj_type);
    }
    context->drag_status(Gdk::ACTION_COPY, timestamp);
    requested_for_motion_ = false;
  } else {
    dnd_item_->remove();
    dnd_item_.reset();
    switch (obj_type) {
    case CIRCLE:
    case RECTANGLE:
    case GENERIC_IMAGE:
    default:
      LevelObject* object = new LevelObject(create_canvas_item(item_x, item_y, icon, obj_type));

      // TODO(Diego): debug - borrar
      std::stringstream ss;
      ss << "Prueba";
      ss << n_borrar_es_para_pruebas++;
      std::string meta_prueba;
      ss >> meta_prueba;
      object->set_property("meta.prueba", meta_prueba);

      controller_->register_object(object);
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
  if (dnd_item_) {
    double item_x = x;  // + canvas_window_->get_hadjustment()->get_value();
    double item_y = y;  // + canvas_window_->get_vadjustment()->get_value();
    convert_from_pixels(item_x, item_y); /* scale to canvas units */
    gdouble t_x, t_y, t_scale, t_rotation;
    dnd_item_->get_simple_transform(t_x, t_y, t_scale, t_rotation);
    dnd_item_->set_simple_transform(item_x, item_y, t_scale, t_rotation);
    context->drag_status(Gdk::ACTION_COPY, timestamp);
  } else {
    /* If item doesn't exist, we should get it's data from the source and create it. It's achieved
    via the drag_get_data method, which in turn emits the drag_data_received signal */
    requested_for_motion_ = true;
    drag_get_data(context, target, timestamp);
  }

  return true;
}

bool EditorCanvas::on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
    guint timestamp) {
  std::cout << "on_canvas_drag_drop " << x << ", " << y << std::endl;
  const Glib::ustring target = drag_dest_find_target(context);
  if (target.empty()) {
    return false;
  }
  drag_get_data(context, target, timestamp);
  return true;
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_item(double x, double y,
    Gtk::Widget* icon, DraggableObjectType obj_type) {
  Glib::RefPtr<Goocanvas::Item> canvas_item;
  switch (obj_type) {
  case CIRCLE:
    canvas_item = create_canvas_circle(x, y);
    break;
  case RECTANGLE:
    canvas_item = create_canvas_rect(x, y);
    break;
  case GENERIC_IMAGE:
  default:
    canvas_item = create_canvas_image(x, y, icon);
    break;
  }
  return canvas_item;
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_image(double x, double y,
    Gtk::Widget* icon) {
  Gtk::Image* image = dynamic_cast<Gtk::Image*>(icon);
  Glib::RefPtr<Goocanvas::Item> img = ImageItem::create(controller_, image->get_pixbuf(), x, y);
  get_root_item()->add_child(img);
  return img;
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_rect(double x, double y) {
  Glib::RefPtr<Goocanvas::Item> rect = Goocanvas::Rect::create(x, y, 64, 32);
  rect->set_property("fill_color", Glib::ustring("blue"));
  get_root_item()->add_child(rect);
  return rect;
}

Glib::RefPtr<Goocanvas::Item> EditorCanvas::create_canvas_circle(double x, double y) {
  Glib::RefPtr<Goocanvas::Item> circle = Goocanvas::Ellipse::create(x, y, 32, 32);
  circle->set_property("fill_color", Glib::ustring("blue"));
  get_root_item()->add_child(circle);
  return circle;
}
