#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <gdkmm/pixbuf.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolitemgroup.h>
#include <goocanvasmm/image.h>
#include <goocanvasmm/rect.h>
#include "EditorLayer.h"
#include "EditorController.h"
#include "EditorCanvas.h"
#include "EditorWindow.h"
#define GLADE_FILENAME "window.glade"
#define MAIN_WINDOW_GLADE_ID "MainBox"
#define PALETTE_GLADE_ID "ToolPalette"
#define CANVAS_CONTAINER_GLADE_ID "CanvasWindow"
#define DRAG_DATA_FORMAT 8

#include <iostream>

EditorWindow::EditorWindow() : canvas_(canvas_window_) {
  set_title("Blues Jackrabbit - Level Editor");
  // TODO(Diego): following line probably not needed.
  set_size_request(640, 480);
  set_position(Gtk::WIN_POS_CENTER);
  maximize();
  load_content_from_glade();

  // TODO(Diego): this should be set after file->new or file->open
  canvas_.set_size_request(3000, 3000);
  canvas_.property_background_color().set_value("black");
  canvas_window_->add(canvas_);
  canvas_.set_bounds(0, 0, 3000, 3000);

  init_palette();

  /* Set drag and drop communication between palette and canvas */
  palette_->add_drag_dest(canvas_, (Gtk::DestDefaults)0, Gtk::TOOL_PALETTE_DRAG_ITEMS,
      Gdk::ACTION_COPY);

  init_menus();
  add(*root_);
  show_all();
}

EditorWindow::~EditorWindow() {
  delete root_;
  delete palette_;
}

void EditorWindow::load_content_from_glade() {
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file(GLADE_FILENAME);
  refBuilder->get_widget(MAIN_WINDOW_GLADE_ID, root_);
  refBuilder->get_widget(PALETTE_GLADE_ID, palette_);
  refBuilder->get_widget(CANVAS_CONTAINER_GLADE_ID, canvas_window_);
}

void EditorWindow::init_palette() {
  tiles_group_ = Gtk::manage(new Gtk::ToolItemGroup("Tiles"));
  control_group_ = Gtk::manage(new Gtk::ToolItemGroup("Control Objects"));
  misc_group_ = Gtk::manage(new Gtk::ToolItemGroup("Miscellaneous"));

  // TODO(Diego): pasar a inicializacion de Assets
  // Asset 1 - Tileset - Brown Nature
  std::string asset_filename = "assets/brown_nature.png";
  Glib::RefPtr<Gdk::Pixbuf> tileset_pixbuf = Gdk::Pixbuf::create_from_file(asset_filename);
  // TODO(Diego): ideally, read properties from an Asset file
  const int tile_width = 64;
  const int tile_height = 64;
  const int tile_qty_v = 8;
  const int tile_qty_h = 8;
  int tile_number = 0;
  for (int cursor_v = 0; cursor_v < tile_qty_v; ++cursor_v) {
    for (int cursor_h = 0; cursor_h < tile_qty_h; ++cursor_h) {
      std::stringstream asset_uid_formatter_stream;
      std::string asset_uid;
      asset_uid_formatter_stream << "brown_nature.";
      asset_uid_formatter_stream << std::setw(4) << std::setfill('0') << tile_number;
      asset_uid_formatter_stream >> asset_uid;
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_subpixbuf(
          tileset_pixbuf, tile_width * cursor_v, tile_height * cursor_h, tile_width, tile_height);
      Gtk::Image* image = Gtk::manage(new Gtk::Image(pixbuf));
      Glib::ustring icon_name = asset_uid;
      Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton(*image, icon_name));
      button->signal_drag_data_get().connect(
          sigc::bind(sigc::mem_fun(*this, &EditorWindow::on_toolbutton_drag_data_get), asset_uid));
      tiles_group_->insert(*button);
    }
  }
  // Asset 2 - Image - Barrel
  asset_filename = "assets/barrel.png";
  Glib::RefPtr<Gdk::Pixbuf> misc_pixbuf = Gdk::Pixbuf::create_from_file(asset_filename);
  Gtk::Image* image = Gtk::manage(new Gtk::Image(
      misc_pixbuf->scale_simple(64, 64, Gdk::INTERP_NEAREST)));
  Glib::ustring icon_name = "Obj1";
  Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton(*image, icon_name));
  misc_group_->insert(*button);

  palette_->add(*tiles_group_);
  palette_->add(*control_group_);
  palette_->add(*misc_group_);
}

void EditorWindow::change_layer(int parameter) {
  action_active_layer_->change_state(parameter);
  controller_.change_layer(parameter);
}

void EditorWindow::init_menus() {
  Glib::RefPtr<Gio::SimpleActionGroup> ag = Gio::SimpleActionGroup::create();
  /* Archivo */
  ag->add_action("new", sigc::mem_fun(controller_, &EditorController::start_new_level));
  /* Ver */
  action_active_layer_ = ag->add_action_radio_integer("activelayer",
      sigc::mem_fun(*this, &EditorWindow::change_layer), TILEMAP);
  action_tilemap_visible_ = ag->add_action_bool("viewtilemap",
      sigc::mem_fun(controller_, &EditorController::tilemap_visible), true);

  insert_action_group("editor", ag);
}

bool EditorWindow::on_canvas_drag_motion(
      const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp) {
  /* Look for a match between source and destination TargetEntries */
  const Glib::ustring target = drag_dest_find_target(drag_context);
  if (target.empty()) {
    return false;
  }

  canvas_.drag_highlight();

  /* If item exists, we're supposed to move it and call drag_status() */
  if (dnd_item_) {
    double item_x = x;  // + canvas_window_->get_hadjustment()->get_value();
    double item_y = y;  // + canvas_window_->get_vadjustment()->get_value();
    canvas_.convert_from_pixels(item_x, item_y); /* scale to canvas units */
    gdouble t_x, t_y, t_scale, t_rotation;
    dnd_item_->get_simple_transform(t_x, t_y, t_scale, t_rotation);
    dnd_item_->set_simple_transform(item_x, item_y, t_scale, t_rotation);
    drag_context->drag_status(Gdk::ACTION_COPY, timestamp);
  } else {
    /* If item doesn't exist, we should get it's data from the source and create it. It's achieved
    via the drag_get_data method, which in turn emits the drag_data_received signal */
    requested_for_motion_ = true;
    canvas_.drag_get_data(drag_context, target, timestamp);
    return true;
  }

  return true;
}

void EditorWindow::on_canvas_drag_data_received(
    const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y,
    const Gtk::SelectionData& selection_data, guint /* info */, guint timestamp) {
  std::cout << selection_data.get_length() << std::endl;

  double item_x = x + canvas_window_->get_hadjustment()->get_value();
  double item_y = y + canvas_window_->get_vadjustment()->get_value();
  canvas_.convert_from_pixels(item_x, item_y);

  /* The following chunk was taken from GNOME Developer's site - gtkmm ToolPalette Tutorial:
  https://developer.gnome.org/gtkmm-tutorial/stable/toolpalette-example.html.en
  in order to get the ToolItem which started the DnD operation */
  Gtk::Widget* widget = drag_get_source_widget(drag_context);

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

  Gtk::Widget* icon = button->get_icon_widget();

  /* This method is called from either drag_motion or drag_drop, and the DragContext has to be
  updated in consequence */
  if (requested_for_motion_) {
    if (!dnd_item_) {
      dnd_item_ = create_canvas_item(item_x, item_y, icon);
    }
    drag_context->drag_status(Gdk::ACTION_COPY, timestamp);
    requested_for_motion_ = false;
  } else {
    dnd_item_->remove();
    dnd_item_.reset();
    create_canvas_item(item_x, item_y, icon);
    drag_context->drag_finish(false, false, timestamp);
  }
}

// TODO(Diego): not needed anymore - kept for debug purposes
Glib::RefPtr<Goocanvas::Item> EditorWindow::create_canvas_item(double x, double y) {
  Glib::RefPtr<Goocanvas::Item> rect = Goocanvas::Rect::create(x, y, 20, 20);
  rect->set_property("fill_color", Glib::ustring("red"));
  canvas_.get_root_item()->add_child(rect);
  return rect;
}

Glib::RefPtr<Goocanvas::Item> EditorWindow::create_canvas_item(double x, double y,
    Gtk::Widget* icon) {
  Gtk::Image* image = dynamic_cast<Gtk::Image*>(icon);
  Glib::RefPtr<Goocanvas::Item> img = Goocanvas::Image::create(image->get_pixbuf(), x, y);
  canvas_.get_root_item()->add_child(img);
  return img;
}

bool EditorWindow::on_canvas_drag_drop(
      const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y, guint timestamp) {
  std::cout << "on_canvas_drag_drop " << x << ", " << y << std::endl;
  const Glib::ustring target = drag_dest_find_target(drag_context);
  if (target.empty()) {
    return false;
  }
  canvas_.drag_get_data(drag_context, target, timestamp);
  return true;
}

void EditorWindow::on_toolbutton_drag_data_get(
    const Glib::RefPtr<Gdk::DragContext>& /* drag_context */, Gtk::SelectionData& selection_data,
    guint /* info */, guint /* time */, std::string asset_uid) {
  // TODO(Diego): sacar linea de debug!!
  std::cout << "EditorWindow::on_button_drag_data_get " << asset_uid << std::endl;

  selection_data.set(selection_data.get_target(), DRAG_DATA_FORMAT, (const guchar*)&asset_uid,
      static_cast<int>(asset_uid.length()));
}
