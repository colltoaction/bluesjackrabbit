#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm/frame.h>
#include <gtkmm/paned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include "SceneRenderer.h"
#include "InitialScreen.h"


class MainWindow : public Gtk::Window {
 public:
    explicit MainWindow(SceneRenderer *scene);
    virtual ~MainWindow();
    void changeOnNewButtonClicked();

 private:
    Gtk::Box mainFrame;
    InitialScreen initialScreen;
    SceneRenderer *scene;
    void loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget);
};

#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
