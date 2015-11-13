#include <gdkmm/pixbuf.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolitemgroup.h>
#include "Editor.h"
#define GLADE_FILENAME "window.glade"
#define MAIN_WINDOW_GLADE_ID "MainBox"
#define PALETTE_GLADE_ID "ToolPalette"
#define CANVAS_CONTAINER_GLADE_ID "CanvasWindow"

Editor::Editor() :
    // level_(),
    unsaved_changes_(false),
    root_(NULL),
    palette_(NULL),
    tiles_group_(NULL),
    control_group_(NULL),
    misc_group_(NULL) {
  set_title("Blues Jackrabbit - Level Editor");
  // TODO(Diego): following line probably not needed.
  set_size_request(640, 480);
  set_position(Gtk::WIN_POS_CENTER);
  maximize();
  load_content_from_glade();

  Gtk::DrawingArea* canvas = Gtk::manage(new Gtk::DrawingArea());
  canvas->set_size_request(3000, 3000);
  canvas_window_->add(*canvas);

  init_palette();
  add(*root_);
  show_all();
}

Editor::~Editor() {
  delete root_;
  delete palette_;
}

void Editor::load_content_from_glade() {
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  refBuilder->add_from_file(GLADE_FILENAME);
  refBuilder->get_widget(MAIN_WINDOW_GLADE_ID, root_);
  refBuilder->get_widget(PALETTE_GLADE_ID, palette_);
  refBuilder->get_widget(CANVAS_CONTAINER_GLADE_ID, canvas_window_);
}

void Editor::init_palette() {
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

void Editor::start_new_level() {
  if (unsaved_changes_) {
    // TODO(Diego): mostrar cuadro de dialogo - guardar cambios?
  }
}
