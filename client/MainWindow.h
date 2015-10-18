#ifndef BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
#define BLUESJACKRABBIT_CLIENT_MAINWINDOW_H

#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
 public:
    explicit MainWindow(EventBus *eventBus);

 private:
    static const unsigned int timeout_value = 10;
};


#endif  // BLUESJACKRABBIT_CLIENT_MAINWINDOW_H
