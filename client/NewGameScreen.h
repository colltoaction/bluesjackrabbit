#ifndef NEWGAMESCREEN_H_
#define NEWGAMESCREEN_H_

#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <gtkmm/paned.h>

class NewGameScreen : public Gtk::Box {
public:
	NewGameScreen();
	virtual ~NewGameScreen();
};

#endif /* NEWGAMESCREEN_H_ */
