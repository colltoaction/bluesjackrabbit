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
#include <common/InvalidMessageException.h>
#include <common/Logger.h>
#include <gtkmm/messagedialog.h>

#include "EventBus.h"
#include "MainWindow.h"
#include "RemoteServerProxy.h"
#include "ServerProxy.h"

MainWindow::MainWindow(const Configuration &config)
    : config_(config)
    , scene_()
    , main_frame_()
    , connection_screen_()
    , initial_screen_()
    , new_game_screen_()
    , join_game_screen_()
    , dispatcher_()
    , text_game_name_(NULL)
    , players_(NULL)
    , server_proxy_(NULL)
    , map_id_(0)
    , game_id_(0)
    , map_combo(NULL)
    , game_combo(NULL) {
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

  dispatcher_.connect(sigc::mem_fun(*this, &MainWindow::show_dialog));

  add(main_frame_);
  main_game_view();

  signal_delete_event().connect(sigc::mem_fun(*this, &MainWindow::on_close_window));

  Glib::signal_timeout().connect(
        sigc::bind_return(sigc::mem_fun(&scene_, &SceneRenderer::update), true),
        render_step);

  show_all();
  scene_.hide();
  initial_screen_.hide();
  new_game_screen_.hide();
  join_game_screen_.hide();
}

MainWindow::~MainWindow() {
  if (server_proxy_ != NULL) {
    delete server_proxy_;
  }
}

void MainWindow::notify_something(std::string message) {
  message_ = message;
  dispatcher_.emit();
}

void MainWindow::show_dialog() {
  Gtk::MessageDialog dialog(*this, message_);
  dialog.run();
  if (message_.find("MATCH") != std::string::npos) {
    main_game_view();
    server_proxy_->reset_updater();
  }
}

bool MainWindow::on_close_window(GdkEventAny* /* any_event */) {
  on_quit_requested();
  return true;  // Stop propagating event
}

void MainWindow::on_quit_requested() {
  if (server_proxy_ != NULL) {
    server_proxy_->shutdown();
  }
  hide();
}

void MainWindow::main_game_view() {
  map_combo_model->clear();
  game_combo_model->clear();
  show_all();
  connection_screen_.hide();
  scene_.hide();
  new_game_screen_.hide();
  join_game_screen_.hide();
  text_game_name_->set_text("");
  players_->set_text("");
  disconnect_bus_signals();
}

void MainWindow::new_game_click() {
  if (connected_) {
    std::map<size_t, std::string> maps = server_proxy_->list_maps();
    load_combo(&map_combo_model, maps);
    initial_screen_.hide();
    new_game_screen_.show();
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
  std::string game_name = text_game_name_->get_text();
  std::string players_size = players_->get_text();
  std::istringstream buffer(players_size);
  int value;
  buffer >> value;
  server_proxy_->start_game(map_id_, game_name, value);
  new_game_screen_.hide();
  connect_bus_signals();
  scene_.show();
}

void MainWindow::connect_bus_signals() {
  add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
  pressed_ = signal_key_press_event().connect(
      sigc::mem_fun(bus_, &EventBus::keyPressEvent), false);
  released_ = signal_key_release_event().connect(
      sigc::mem_fun(bus_, &EventBus::keyReleaseEvent), false);
}

void MainWindow::disconnect_bus_signals() {
  pressed_.disconnect();
  released_.disconnect();
}

void MainWindow::multiplayer_click() {
  server_proxy_ = new RemoteServerProxy(config_, sigc::mem_fun(*this, &MainWindow::main_game_view)
      , sigc::mem_fun(*this, &MainWindow::notify_something));
  init_server_proxy();
  main_game_view();
}

void MainWindow::init_server_proxy() {
  try {
    server_proxy_->connect();
  } catch (const InvalidMessageException &ex) {
    Logger::info(ex.what());
    connected_ = false;
    Gtk::MessageDialog dialog(*this, "Error al conectarse al servidor.");
    dialog.set_secondary_text("Hubo un error al conectarse al servidor. Asegurese que esta ejecutandose.");
    dialog.run();
    hide();
    return;
  }

  connected_ = true;
  bus_.subscribeKeyPress(GDK_KEY_Up, sigc::hide(sigc::mem_fun(server_proxy_, &ServerProxy::MoveUp)));
  bus_.subscribeKeyPress(GDK_KEY_Down, sigc::hide(sigc::mem_fun(server_proxy_, &ServerProxy::MoveDown)));
  bus_.subscribeKeyPress(GDK_KEY_Left, sigc::hide(sigc::mem_fun(server_proxy_, &ServerProxy::MoveLeft)));
  bus_.subscribeKeyPress(GDK_KEY_Right, sigc::hide(sigc::mem_fun(server_proxy_, &ServerProxy::MoveRight)));
  bus_.subscribeKeyPress(GDK_KEY_space, sigc::hide(sigc::mem_fun(server_proxy_, &ServerProxy::jump)));
  bus_.subscribeKeyPress(GDK_KEY_Control_L, sigc::hide(sigc::mem_fun(server_proxy_, &ServerProxy::shoot)));
  scene_.set_server_proxy(server_proxy_);
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
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/main_frame.glade", &initial_screen_);
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
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_quit_requested));
  }
}

void MainWindow::init_connect_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/connect.glade", &connection_screen_);
  Gtk::Button *button = NULL;
  builder->get_widget("button_multiplayer", button);
  if (button) {
      button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::multiplayer_click));
  }
}


void MainWindow::init_new_game_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/new_game.glade", &new_game_screen_);
  Gtk::Button *button = NULL;
  builder->get_widget("start", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::init_click));
  }
  button = NULL;
  builder->get_widget("cancel", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::main_game_view));
  }
  builder->get_widget("game_name", text_game_name_);
  builder->get_widget("players", players_);
  builder->get_widget("map", map_combo);
  // Create the Combobox Tree model:
  map_combo_model = Gtk::ListStore::create(columns);
  map_combo->set_model(map_combo_model);
  map_combo->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::combo_map_changed));
  map_combo->pack_start(columns.id);
  map_combo->pack_start(columns.map_name);
}

void MainWindow::combo_map_changed() {
  map_id_ = ((*map_combo->get_active())[columns.id]);
}

void MainWindow::combo_game_changed() {
  game_id_ = ((*game_combo->get_active())[columns.id]);
}

void MainWindow::init_join_game_screen() {
  Glib::RefPtr<Gtk::Builder> builder = load_from_glade("static/join_game.glade", &join_game_screen_);
  Gtk::Button *button = NULL;
  builder->get_widget("cancel", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::main_game_view));
  }
  button = NULL;
  builder->get_widget("join", button);
  if (button) {
    button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::join_once_for_all));
  }

  builder->get_widget("games", game_combo);
    // Create the Combobox Tree model:
  game_combo_model = Gtk::ListStore::create(columns);
  game_combo->set_model(game_combo_model);
  game_combo->signal_changed().connect(sigc::mem_fun(*this, &MainWindow::combo_game_changed));
  game_combo->pack_start(columns.id);
  game_combo->pack_start(columns.map_name);
}

void MainWindow::load_combo(Glib::RefPtr<Gtk::ListStore> *model, const std::map<size_t, std::string> &names) {
  for (std::map<size_t, std::string>::const_iterator it = names.begin(); it != names.end(); it++) {
    Gtk::TreeModel::Row row = *((*model)->append());
    row[columns.id] = it->first;
    row[columns.map_name] = it->second;
    // map_combo->set_active(row);
  }
}
