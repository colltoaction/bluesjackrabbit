// Este include no iria. Deberiamos lanzar excepcion en caso de no encontrar archivo.
#include <iostream>
#include <glibmm/main.h>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/paned.h>
#include <gtkmm/messagedialog.h>

#include "EventBus.h"
#include "LocalServerProxy.h"
#include "MainWindow.h"
#include "ServerProxy.h"

MainWindow::MainWindow(SceneRenderer *scene, ServerProxy *server_proxy)
  : main_frame(),
    initial_screen(),
    new_game_screen(),
    map_id(0),
    scene(scene),
    map_combo(NULL) {
  this->server_proxy = server_proxy;
  set_title("Blues Jackrabbit");
  set_size_request(640, 480);
  set_position(Gtk::WIN_POS_CENTER);

  init_connect_screen();
  init_main_game_screen();
  init_new_game_screen();
  init_join_game_screen();

  main_frame_.pack_start(scene_);
  main_frame_.pack_start(connection_screen_);
  main_frame_.pack_start(initial_screen_);
  main_frame_.pack_start(new_game_screen_);
  main_frame_.pack_start(join_game_screen_);

  add(main_frame_);
  main_game_view();

  signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::on_close_window));

  Glib::signal_timeout().connect(
        sigc::bind_return(sigc::mem_fun(&scene_, &SceneRenderer::update), true),
        render_step);


  show_all();
  scene->hide();
  new_game_screen.hide();
  join_game_screen.hide();

  connected = this->server_proxy->connect();
  std::cout << ((connected) ?"OK" : "NO") << std::endl;
}

MainWindow::~MainWindow() {
  if (server_proxy_ != NULL) {
    delete server_proxy_;
  }
}

// TODO(tomas) No puede ser que no se pueda cerrar sin exit
bool MainWindow::on_close_window(GdkEventAny* any_event) {
  (void)any_event;
  server_proxy_->shutdown();
  hide();
  exit(0);
  return true;  // Propagate event
}

void MainWindow::main_game_view() {
  map_combo_model->clear();
  game_combo_model->clear();
  show_all();
  connection_screen_.hide();
  scene_.hide();
  new_game_screen_.hide();
  join_game_screen_.hide();
}

void MainWindow::new_game_click() {
  if (connected) {
    std::map<size_t, std::string> maps = server_proxy->list_maps();
    load_combo(maps);
    initial_screen.hide();
    new_game_screen.show();
  }
}

void MainWindow::join_game_click() {
  if (connected_) {
    std::map<size_t, std::string> games = server_proxy_->list_games();
    load_combo(&game_combo_model, games);
    initial_screen_.hide();
    join_game_screen_.show();
  }
}

void MainWindow::join_once_for_all() {
  if (connected_) {
    server_proxy_->join_game(game_id_);
    join_game_screen_.hide();
    connect_bus_signals();
    scene_.show();
  }
}

void MainWindow::init_click() {
  server_proxy->start_game(map_id);
  new_game_screen.hide();
  scene->show();
}

Glib::RefPtr<Gtk::Builder> MainWindow::load_from_glade(std::string file_name, Gtk::Box *parent) {
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file(file_name);
  } catch (const Glib::FileError &ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
  } catch (const Glib::MarkupError &ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
  } catch (const Gtk::BuilderError &ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }
  // FRAME HARDCODE. AL menos que todos los glade lo llamen frame y listo.
  Gtk::Widget *other;
  refBuilder->get_widget("frame", other);
  other->reparent(*parent);
  return refBuilder;
}

void MainWindow::init_main_game_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/main_frame.glade", &initial_screen);
  Gtk::Button *button = NULL;
  builder->get_widget("buttonNewGame", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::new_game_click));
  }
  button = NULL;
  builder->get_widget("buttonJoinGame", button);
  if (button) {
      button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::join_game_click));
  }
  button = NULL;
  builder->get_widget("buttonExit", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::hide));
  }
}

void MainWindow::init_connect_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/connect.glade", &connection_screen_);
  Gtk::Button *button = NULL;
  builder->get_widget("button_singleplayer", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::singleplayer_click));
  }
  button = NULL;
  builder->get_widget("button_multiplayer", button);
  if (button) {
      button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::multiplayer_click));
  }
}


void MainWindow::init_new_game_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/new_game.glade", &new_game_screen);
  Gtk::Button *button = NULL;
  builder->get_widget("start", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::init_click));
  }
  builder->get_widget("map", map_combo);
  // Create the Combobox Tree model:
  combo_model = Gtk::ListStore::create(columns);
  map_combo->set_model(combo_model);
  map_combo->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::combo_map_changed));
  map_combo->pack_start(columns.id);
  map_combo->pack_start(columns.map_name);
}

void MainWindow::combo_map_changed() {
  // std::cout << ((*map_combo->get_active())[columns.id]) << std::endl;
  map_id = ((*map_combo->get_active())[columns.id]);
}

void MainWindow::init_join_game_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/join_game.glade", &join_game_screen);
}


void MainWindow::load_combo(const std::map<size_t, std::string> &names) {
  for (std::map<size_t, std::string>::const_iterator it = names.begin(); it != names.end(); it++) {
    Gtk::TreeModel::Row row = *(combo_model->append());
    row[columns.id] = it->first;
    row[columns.map_name] = it->second;
    // map_combo->set_active(row);
  }
}
