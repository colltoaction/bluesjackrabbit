#ifndef BLUESJACKRABBIT_CLIENT_INITIALSCREEN_H
#define BLUESJACKRABBIT_CLIENT_INITIALSCREEN_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>


typedef sigc::slot<void> Clickeable;

class InitialScreen : public Gtk::Box {
 public:
    explicit InitialScreen(Clickeable clickable);
    virtual ~InitialScreen();

 private:
    Gtk::Button newGameButton;
    Gtk::Button joinGameButton;
    Gtk::Button exitButton;
};

#endif  // BLUESJACKRABBIT_CLIENT_INITIALSCREEN_H
