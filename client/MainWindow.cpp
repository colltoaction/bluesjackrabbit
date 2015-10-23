// Este include no iria. Deberiamos lanzar excepcion en caso de no encontrar archivo.
#include <iostream>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <gtkmm/builder.h>

#include "EventBus.h"
#include "MainWindow.h"


MainWindow::MainWindow(SceneRenderer *scene)
        : mainFrame(),
          //
          initialScreen(),
          newGameScreen(),
          scene(scene) {
    set_title("Blues Jackrabbit");
    set_resizable(false);
    set_size_request(640, 480);
    set_position(Gtk::WIN_POS_CENTER);

    loadFrameFromGlade("main_frame.glade", &initialScreen);
    loadFrameFromGlade("new_game.glade", &newGameScreen);

    //sigc::mem_fun(*this, &MainWindow::changeOnNewButtonClicked);

    mainFrame.pack_start(*scene);
    mainFrame.pack_start(initialScreen);
    mainFrame.pack_start(newGameScreen);

    add(mainFrame);
    show_all();
    //scene->hide();
    //newGameScreen.hide();
}

MainWindow::~MainWindow() {
}

void MainWindow::changeOnNewButtonClicked() {
    initialScreen.hide();
    newGameScreen.show();
}

void MainWindow::loadFrameFromGlade(std::string fileName, Gtk::Widget *parent) {
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
    Gtk::Widget *other;
    refBuilder->get_widget("frame", other);
    other->reparent(*parent);
}

