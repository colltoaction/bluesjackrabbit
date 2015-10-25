/* Compile with:  
*       gcc -Wall -o csswindow `pkg-config --cflags --libs gtk+-3.0` csswindow.c                            
*/
#include <gtkmm/application.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/window.h>

int main(int argc, char *argv[]) {
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
  Gtk::Window window;
/*--- CSS -----------------*/
  Glib::RefPtr<Gtk::CssProvider> provider = Gtk::CssProvider::create();
  Glib::RefPtr<Gtk::StyleContext> style_context = window.get_style_context();
/*-------------------------*/

  window.set_default_size(500, 300);

/*------  CSS  ----------------------------------------------------------------------------------------*/
  provider->load_from_path("jazz.css");
  style_context->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
/*----------------------------------------------------------------------------------------------------------*/

  return app->run(window);
}
