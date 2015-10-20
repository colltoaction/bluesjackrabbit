#include <gtkmm.h>
#include <iostream>

int main(int argc, char **argv) {
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    std::string file = "window.glade";
    if (argc > 1) {
        file = std::string(argv[1]);
    }

    // Load the GtkBuilder file and instantiate its widgets:
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file(file);
    } catch(const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    } catch(const Glib::MarkupError& ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    } catch(const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    // Get the GtkBuilder-instantiated Dialog:
    Gtk::Window* window = NULL;
    refBuilder->get_widget("MainWindow", window);
    if (window) {
        app->run(*window);
    }
    delete window;
    return 0;
}
