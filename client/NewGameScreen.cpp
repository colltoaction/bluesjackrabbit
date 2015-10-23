#include <iostream>
#include "NewGameScreen.h"

NewGameScreen::NewGameScreen() {
  Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
  try {
    refBuilder->add_from_file("new_game.glade");
  } catch (const Glib::FileError &ex) {
    std::cerr << "FileError: " << ex.what() << std::endl;
  } catch (const Glib::MarkupError &ex) {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
  } catch (const Gtk::BuilderError &ex) {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
  }

  // FRAME HARDCODE. AL menos que todos los glade lo llamen frame y listo.
  Gtk::Paned *mainWidget;
  refBuilder->get_widget("frame", mainWidget);
  mainWidget->reparent(*this);
}

NewGameScreen::~NewGameScreen() {
}

