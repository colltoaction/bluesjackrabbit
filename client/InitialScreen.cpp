#include "InitialScreen.h"
#include <iostream>

InitialScreen::InitialScreen(Clickeable clickable) {
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file("main_frame.glade");
    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    // FRAME HARDCODE. AL menos que todos los glade lo llamen frame y listo.
    Gtk::Frame *mainWidget;
    refBuilder->get_widget("frame", mainWidget);
    mainWidget->reparent(*this);

    Gtk::Button *newGameButton;
    refBuilder->get_widget("butttonNewGame", newGameButton);

    newGameButton->signal_clicked().connect(clickable);
}

InitialScreen::~InitialScreen() {
}

