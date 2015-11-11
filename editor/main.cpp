// TODO(Diego): incluir solamente lo que se usa
#include <gtkmm.h>
#include <iostream>
#define GLADE_FILENAME "window.glade"
#define MAIN_WINDOW_GLADE_ID "MainWindow"
#define PALETTE_GLADE_ID "ToolPalette"
#define RC_OK 0

int main(int argc, char **argv) {
  int ret_code = RC_OK;
  Glib::RefPtr<Gtk::Application> app =
      Gtk::Application::create(argc, argv, "ar.uba.fi.tallerprog.blues.editor");
  std::string file = GLADE_FILENAME;

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
  Gtk::ToolPalette* tool_palette = NULL;
  Gtk::ToolItemGroup* group1 = Gtk::manage(new Gtk::ToolItemGroup("Tiles"));
  Gtk::ToolItemGroup* group2 = Gtk::manage(new Gtk::ToolItemGroup("Control Objects"));
  Gtk::ToolItemGroup* group3 = Gtk::manage(new Gtk::ToolItemGroup("Miscellaneous"));
  Gtk::DrawingArea* canvas = Gtk::manage(new Gtk::DrawingArea());
  Gtk::Viewport* canvas_viewport = NULL;
  // TODO(Diego): try/catch
  Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("assets/barrel.png");
  Gtk::Image* image = Gtk::manage(new Gtk::Image(pixbuf));
  Glib::ustring icon_name = "Obj1";
  Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton(*image, icon_name));
  button->set_tooltip_text(icon_name);
  button->set_is_important();

  refBuilder->get_widget(MAIN_WINDOW_GLADE_ID, window);
  refBuilder->get_widget(PALETTE_GLADE_ID, tool_palette);
  refBuilder->get_widget("CanvasViewport", canvas_viewport);

  if (window) {
    window->set_size_request(300, 100);
    window->maximize();

    canvas->set_size_request(3000, 3000);
    canvas_viewport->add(*canvas);

    group1->insert(*button);

    tool_palette->add(*group1);
    tool_palette->add(*group2);
    tool_palette->add(*group3);
    ret_code = app->run(*window);
    delete window;
  }

  return ret_code;
}
