#ifndef BLUESJACKRABBIT_CLIENT_INITIALSCREEN_H
#define BLUESJACKRABBIT_CLIENT_INITIALSCREEN_H

#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>

typedef sigc::slot<void> Clickeable;

class InitialScreen : public Gtk::Box {
 public:
    explicit InitialScreen(Clickeable clickable);
    virtual ~InitialScreen();
};

#endif  // BLUESJACKRABBIT_CLIENT_INITIALSCREEN_H
