#include <string>
#include <gtkmm/image.h>
#include "CustomToolButton.h"
#include "ControlToolButton.h"

ControlToolButton::ControlToolButton(std::string filename, std::string label,
    int width, int height) : CustomToolButton(label, width, height) {
  std::string asset_filename = "assets/" + filename;
  Glib::RefPtr<Gdk::Pixbuf> misc_pixbuf = Gdk::Pixbuf::create_from_file(asset_filename);
  Gtk::Image* image = Gtk::manage(new Gtk::Image(
      misc_pixbuf->scale_simple(width, height, Gdk::INTERP_NEAREST)));
  set_icon_widget(*image);
}
