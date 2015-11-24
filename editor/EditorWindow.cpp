#include <iomanip>
#include <sstream>
#include <string>
#include <gdkmm/pixbuf.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolitemgroup.h>
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
  delete canvas_window_;
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

void EditorWindow::init_menus() {
  Glib::RefPtr<Gio::SimpleActionGroup> ag = Gio::SimpleActionGroup::create();
  /* Archivo */
  Glib::RefPtr<Gio::SimpleAction> action_new = Gio::SimpleAction::create("new");
  action_new->signal_activate().connect(
      sigc::mem_fun<const Glib::VariantBase&>(controller_, &EditorController::start_new_level));
  ag->add_action(action_new);
  /* Ver */
  insert_action_group("editor", ag);
}
