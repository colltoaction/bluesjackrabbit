#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm/frame.h>
#include <gtkmm/paned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include "NewGameScreen.h"
#include "SceneRenderer.h"

typedef sigc::slot<void> Clickeable;

class MainWindow: public Gtk::Window {
 public:
  explicit MainWindow(SceneRenderer *scene);
  virtual ~MainWindow();
  void new_game_click();

 private:
  Gtk::Box main_frame;
  Gtk::Box initial_screen;
  Gtk::Box new_game_screen;

  SceneRenderer *scene;
  void load_from_glade(std::string file_name, Gtk::Widget *parent, bool signal);
};

#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
