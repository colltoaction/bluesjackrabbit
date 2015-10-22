#include "InitialScreen.h"
#include "Clickeable.h"

InitialScreen::InitialScreen(Clickeable *mainWindow)
    : newGameButton("Nueva Partida"),
      joinGameButton("Unirse a Partida"),
      exitButton("Salir") {
    this->set_visible(true);
    this->set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(newGameButton);
    add(joinGameButton);
    add(exitButton);

    newGameButton.signal_clicked().connect(
            sigc::mem_fun(*mainWindow, &Clickeable::onClick));
}
InitialScreen::~InitialScreen() {
}

