#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H


#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/frame.h>
#include <gtkmm/paned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include "SceneRenderer.h"
#include "ServerProxy.h"
#include "MapComboBox.h"

class MainWindow: public Gtk::Window {
 public:
  explicit MainWindow(SceneRenderer *scene, const ServerProxy &sever_proxy);
  virtual ~MainWindow();

 private:
  Gtk::Box main_frame;
  Gtk::Box initial_screen;
  Gtk::Box new_game_screen;
  Gtk::Box join_game_screen;

  bool connected;
  ServerProxy server_proxy;


  SceneRenderer *scene;
  MapComboBox *map;
  void test();

  Glib::RefPtr<Gtk::Builder> load_from_glade(std::string file_name, Gtk::Box *parent);
  void init_main_game_screen();
  void init_new_game_screen();
  void init_join_game_screen();

  void new_game_click();
  void init_click();
  void join_game_click();
};

#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
