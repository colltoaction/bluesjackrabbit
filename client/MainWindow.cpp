// Este include no iria. Deberiamos lanzar excepcion en caso de no encontrar archivo.
#include <iostream>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <gtkmm/builder.h>

#include "EventBus.h"
#include "MainWindow.h"


MainWindow::MainWindow(SceneRenderer *scene) : mainFrame(),
	initialScreen(this), scene(scene){
    set_title("Blues Jackrabbit");
    set_resizable(false);
    set_size_request(640, 480);
    set_position(Gtk::WIN_POS_CENTER);
	mainFrame.pack_start(*this->scene);
	mainFrame.pack_start(initialScreen);
    this->add(mainFrame);
    show_all();
    scene->hide();
}

MainWindow::~MainWindow(){
}

void MainWindow::changeOnNewButtonClicked(){
	initialScreen.hide();
	scene->show();
}

void MainWindow::onClick(){
	this->changeOnNewButtonClicked();
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
