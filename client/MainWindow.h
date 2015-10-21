#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm/frame.h>
#include <gtkmm/paned.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
 private:
    Gtk::Frame *mainFrame;
    Gtk::Paned *newGamePane;

 public:
    MainWindow();
    virtual ~MainWindow();
    void loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget);
};


#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
