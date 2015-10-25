/* Compile with:  
*       gcc -Wall -o csswindow `pkg-config --cflags --libs gtk+-3.0` csswindow.c                            
*/
#include <gtkmm.h>
#include <gtkmm/cssprovider.h>

int main (int argc, char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
  	Gtk::Window window;
/*--- CSS -----------------*/
	Glib::RefPtr<Gtk::CssProvider> provider;
	Glib::RefPtr<Gtk::StyleContext> style_context;
/*-------------------------*/

	window.set_default_size(500, 300); 

/*------  CSS  ----------------------------------------------------------------------------------------*/
	provider = Gtk::CssProvider::create();
	style_context = window.get_style_context();
	style_context->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	provider->load_from_path("jazz.css");
/*----------------------------------------------------------------------------------------------------------*/

  return app->run(window);
}
