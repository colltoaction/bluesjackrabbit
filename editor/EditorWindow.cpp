#include <iomanip>
#include <sstream>
#include <string>
#include <gdkmm/pixbuf.h>
#include <gtkmm/builder.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/image.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toolitemgroup.h>
#include "BreakableRectButton.h"
#include "CircleButton.h"
#include "EditorLayer.h"
#include "EditorController.h"
#include "EditorCanvas.h"
#include "GoalButton.h"
#include "RectButton.h"
#include "SpawnPointButton.h"
#include "StartPointButton.h"
#include "EditorWindow.h"
#define GLADE_FILENAME "window.glade"
#define MAIN_WINDOW_GLADE_ID "MainBox"
#define PALETTE_GLADE_ID "ToolPalette"
#define CANVAS_CONTAINER_GLADE_ID "CanvasWindow"
#define DRAG_DATA_FORMAT 8

#include <iostream>

EditorWindow::EditorWindow()
    : refBuilder_(Gtk::Builder::create())
    , canvas_(canvas_window_, &controller_) {
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
  refBuilder_->add_from_file(GLADE_FILENAME);
  refBuilder_->get_widget(MAIN_WINDOW_GLADE_ID, root_);
  refBuilder_->get_widget(PALETTE_GLADE_ID, palette_);
  refBuilder_->get_widget(CANVAS_CONTAINER_GLADE_ID, canvas_window_);
}

void EditorWindow::init_palette() {
  control_group_ = Gtk::manage(new Gtk::ToolItemGroup("Control Objects"));
  misc_group_ = Gtk::manage(new Gtk::ToolItemGroup("Visible Objects"));

  std::string asset_filename;

  // TODO(Diego): pasar a codigo de inicializacion de Assets generico
  // Asset 2 - Image - Barrel
  // asset_filename = "assets/barrel.png";
  // Glib::RefPtr<Gdk::Pixbuf> misc_pixbuf = Gdk::Pixbuf::create_from_file(asset_filename);
  // Gtk::Image* image = Gtk::manage(new Gtk::Image(
  //     misc_pixbuf->scale_simple(64, 64, Gdk::INTERP_NEAREST)));
  // Glib::ustring icon_name = "barrel.png";
  Gtk::ToolButton* button;  // = Gtk::manage(new Gtk::ToolButton(*image, icon_name));
  // misc_group_->insert(*button);

  // Special assets: rectangle and circle
  // Circle no tiene soporte en el juego
  // button = Gtk::manage(new CircleButton("Circle"));
  // misc_group_->insert(*button);
  button = Gtk::manage(new RectButton("Floor"));
  misc_group_->insert(*button);
  button = Gtk::manage(new BreakableRectButton("Breakable Floor"));
  misc_group_->insert(*button);

  // Control objects
  button = Gtk::manage(new StartPointButton());
  control_group_->insert(*button);
  button = Gtk::manage(new SpawnPointButton());
  control_group_->insert(*button);
  button = Gtk::manage(new GoalButton());
  control_group_->insert(*button);

  palette_->add(*misc_group_);
  palette_->add(*control_group_);
}

void EditorWindow::init_menus() {
  Glib::RefPtr<Gio::SimpleActionGroup> ag = Gio::SimpleActionGroup::create();
  /* Archivo */
  Glib::RefPtr<Gio::SimpleAction> action_new = Gio::SimpleAction::create("new");
  action_new->signal_activate().connect(
      sigc::mem_fun<const Glib::VariantBase&>(controller_, &EditorController::start_new_level));
  action_new->signal_activate().connect(
      sigc::mem_fun<const Glib::VariantBase&>(canvas_, &EditorCanvas::clear_canvas));

  Glib::RefPtr<Gio::SimpleAction> action_save = Gio::SimpleAction::create("save");
  action_save->signal_activate().connect(
      sigc::mem_fun<const Glib::VariantBase&>(controller_, &EditorController::save_file));

  Glib::RefPtr<Gio::SimpleAction> action_export = Gio::SimpleAction::create("export");
  action_export->signal_activate().connect(
      sigc::mem_fun<const Glib::VariantBase&>(controller_, &EditorController::export_map));
  // action_export->signal_activate().connect(
  //   sigc::mem_fun<const Glib::VariantBase&>(canvas_, &EditorCanvas::clear_canvas));

  ag->add_action(action_new);
  ag->add_action(action_save);
  ag->add_action(action_export);
  /* Ver */
  insert_action_group("editor", ag);
}
