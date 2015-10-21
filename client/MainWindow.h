#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm.h>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>

class MainWindow : public Gtk::Window {
 private:
    Gtk::Frame *mainFrame;
    Gtk::Paned *newGamePane;
 public:
    explicit MainWindow(EventBus *eventBus);
    virtual ~MainWindow();
    void loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget);

 private:
    static const unsigned int timeout_value = 1;  // smallest timeout avaiable
};


#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
