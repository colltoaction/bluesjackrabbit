#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm.h>
#include "Clickeable.h"
#include "SceneRenderer.h"
#include "InitialScreen.h"


class MainWindow : public Gtk::Window, public Clickeable {
 private:
    Gtk::Box mainFrame;
    InitialScreen initialScreen;
    SceneRenderer *scene;


 public:
    explicit MainWindow(SceneRenderer *scene);
    virtual ~MainWindow();
    void loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget);
    void changeOnNewButtonClicked();
    void onClick();
};


#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
