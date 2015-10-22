#ifndef INITIALSCREEN_H_
#define INITIALSCREEN_H_

#include <gtkmm.h>
#include "Clickeable.h"

class InitialScreen : public Gtk::Box {
public:
	InitialScreen(Clickeable *mainWindow);
	virtual ~InitialScreen();
private:
	Gtk::Button newGameButton;
	Gtk::Button joinGameButton;
	Gtk::Button exitButton;
};

#endif /* INITIALSCREEN_H_ */
