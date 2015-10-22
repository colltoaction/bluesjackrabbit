#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm.h>
#include "InitialScreen.h"
#include "SceneRenderer.h"

class MainWindow : public Gtk::Window {
 private:
    Gtk::Box mainFrame;
    InitialScreen initialScreen;
    Gtk::Paned *newGamePane;
    SceneRenderer *scene;

 public:
    MainWindow();
    virtual ~MainWindow();
    void addScene(SceneRenderer *scene);
    void loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget);
};


#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
