#include <vector>
#include <gdkmm/pixbuf.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include <gtkmm/targetentry.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolitemgroup.h>
#include <goocanvasmm/canvas.h>
#include <goocanvasmm/rect.h>
#include "EditorLayer.h"
#include "EditorController.h"
#include "EditorWindow.h"
#define GLADE_FILENAME "window.glade"
#define MAIN_WINDOW_GLADE_ID "MainBox"
#define PALETTE_GLADE_ID "ToolPalette"
#define CANVAS_CONTAINER_GLADE_ID "CanvasWindow"
#define DRAG_DATA_FORMAT 8

#include <iostream>

EditorWindow::EditorWindow() {
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
  /* The following line is a workaround. palette->add_drag_dest also adds some default
  behaviors that conflicts with custom handlers for DnD signals. Re-setting 0 as default
  destination behavior makes it work.
  Ref: https://mail.gnome.org/archives/gtk-list/2007-December/msg00087.html */
  canvas_.drag_dest_set((Gtk::DestDefaults)0, Gdk::ACTION_COPY);
  canvas_.signal_drag_motion().connect(
      sigc::mem_fun(*this, &EditorWindow::on_canvas_drag_motion) );
  canvas_.signal_drag_drop().connect(
      sigc::mem_fun(*this, &EditorWindow::on_canvas_drag_drop) );
  canvas_.signal_drag_data_received().connect(
      sigc::mem_fun(*this, &EditorWindow::on_canvas_drag_data_received) );
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
  std::string asset_filename = "assets/brown_nature.png";
  Glib::RefPtr<Gdk::Pixbuf> tileset_pixbuf = Gdk::Pixbuf::create_from_file(asset_filename);
  int tile_width = 64;
  int tile_height = 64;
  int tile_qty_v = 8;
  int tile_qty_h = 8;
  for (int cursor_v = 0; cursor_v < tile_qty_v; ++cursor_v) {
    for (int cursor_h = 0; cursor_h < tile_qty_h; ++cursor_h) {
      Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_subpixbuf(
          tileset_pixbuf, tile_width * cursor_v, tile_height * cursor_h, tile_width, tile_height);
      Gtk::Image* image = Gtk::manage(new Gtk::Image(pixbuf));
      Glib::ustring icon_name = "Obj1";
      Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton(*image, icon_name));
      tiles_group_->insert(*button);
    }
  }
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
  std::cout << "on_canvas_drag_motion" << std::endl;
  /* Look for a match between source and destination TargetEntries */
  const Glib::ustring target = drag_dest_find_target(drag_context);
  if (target.empty()) {
    return false;
  }

  canvas_.drag_highlight();

  /* If item exists, we're supposed to move it and call drag_status() */
  if (dnd_item_) {
    // TODO(Diego): sacar linea de debug!!!
    std::cout << "on_canvas_drag_motion: dnd_item creado" << std::endl;
    double item_x = x;
    double item_y = y;
    canvas_.convert_from_pixels(item_x, item_y); /* scale to canvas units */
    gdouble t_x, t_y, t_scale, t_rotation;
    dnd_item_->get_simple_transform(t_x, t_y, t_scale, t_rotation);
    dnd_item_->set_simple_transform(item_x, item_y, t_scale, t_rotation);
    drag_context->drag_status(Gdk::ACTION_COPY, timestamp);
  } else {
    /* If item doesn't exist, we should get it's data from the source and create it. It's achieved
    via the drag_get_data method, which in turn emits the drag_data_received signal */
    std::cout << "on_canvas_drag_motion: dnd_item por crearse" << std::endl;
    requested_for_motion_ = true;
    canvas_.drag_get_data(drag_context, target, timestamp);
    return true;
    // td::cout << "on_canvas_drag_motion: despues de drag_get_data" << std::endl;
  }

  return true;
}

void EditorWindow::on_canvas_drag_data_received(
    const Glib::RefPtr<Gdk::DragContext>& drag_context, int x, int y,
    const Gtk::SelectionData& /* selection_data */, guint /* info */, guint timestamp) {
  // TODO(Diego): sacar linea de debug!!!
  std::cout << "on_canvas_drag_data_received" << std::endl;
  if (!dnd_item_) {
    dnd_item_ = create_canvas_item(x, y);
  }
  /* This method is called from either drag_motion or drag_drop, and the DragContext has to be
  updated in consequence */
  if (requested_for_motion_) {
    drag_context->drag_status(Gdk::ACTION_COPY, timestamp);
    requested_for_motion_ = false;
  } else {
    drag_context->drag_finish(false, false, timestamp);
  }
}

Glib::RefPtr<Goocanvas::Item> EditorWindow::create_canvas_item(int x, int y) {
  double item_x = x;
  double item_y = y;
  // canvas_.convert_from_pixels(item_x, item_y);
  Glib::RefPtr<Goocanvas::Item> rect = Goocanvas::Rect::create(item_x, item_y, 20, 20);
  rect->set_property("fill_color", Glib::ustring("red"));
  canvas_.get_root_item()->add_child(rect);
  return rect;
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
