#include "InitialScreen.h"

InitialScreen::InitialScreen(Clickeable clickable)
        : newGameButton("Nueva Partida"),
          joinGameButton("Unirse a Partida"),
          exitButton("Salir") {
    set_visible(true);
    set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(newGameButton);
    add(joinGameButton);
    add(exitButton);

    newGameButton.signal_clicked().connect(clickable);
}

InitialScreen::~InitialScreen() {
}

