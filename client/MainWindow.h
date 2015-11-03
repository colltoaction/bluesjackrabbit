#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H


#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/frame.h>
#include <gtkmm/paned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include "SceneRenderer.h"
#include "ServerProxy.h"

class MainWindow: public Gtk::Window {
 public:
  explicit MainWindow(SceneRenderer *scene, ServerProxy *sever_proxy);
  virtual ~MainWindow();

 private:
  Gtk::Box main_frame;
  Gtk::Box initial_screen;
  Gtk::Box new_game_screen;
  Gtk::Box join_game_screen;

  bool connected;
  ServerProxy *server_proxy;
  size_t map_id;

  Glib::RefPtr<Gtk::Builder> load_from_glade(std::string file_name, Gtk::Box *parent);
  void init_main_game_screen();
  void init_new_game_screen();
  void init_join_game_screen();

  void new_game_click();
  void init_click();
  void join_game_click();

  // Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord {
   public:
      ModelColumns() {
        add(id);
        add(map_name);
      }

      Gtk::TreeModelColumn<size_t> id;
      Gtk::TreeModelColumn<Glib::ustring> map_name;
  };

  ModelColumns columns;
  Glib::RefPtr<Gtk::ListStore> combo_model;

  SceneRenderer *scene;
  Gtk::ComboBox *map_combo;
  void combo_map_changed();
  void load_combo(const std::map<size_t, std::string> &names);
};

#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
