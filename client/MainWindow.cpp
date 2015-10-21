// Este include no iria. Deberiamos lanzar excepcion en caso de no encontrar archivo.
#include <iostream>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <gtkmm/builder.h>


#include "EventBus.h"
#include "MainWindow.h"

MainWindow::MainWindow() {
    set_title("Blues Jackrabbit");
    set_resizable(false);
    set_size_request(300, 100);
    set_position(Gtk::WIN_POS_CENTER);
    loadFrameFromGlade("new_game.glade", newGamePane);
    maximize();
}

MainWindow::~MainWindow() {
}

void MainWindow::loadFrameFromGlade(std::string fileName, Gtk::Widget *mainWidget) {
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file(fileName);
    } catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
    } catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    } catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

    // FRAME HARDCODE. AL menos que todos los glade lo llamen frame y listo.
    refBuilder->get_widget("frame", mainWidget);
    mainWidget->reparent(*this);
}
