#include "CustomToolButton.h"

CustomToolButton::CustomToolButton(const Glib::ustring& label, int width, int height)
    : Gtk::ToolButton(label), width_(width), height_(height) {
}

void CustomToolButton::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const {
  minimum_width = width_;
  natural_width = width_;
}

void CustomToolButton::get_preferred_width_for_height_vfunc(int /* height */, int& minimum_width,
    int& natural_width) const {
  minimum_width = width_;
  natural_width = width_;
}

void CustomToolButton::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const {
  minimum_height = height_;
  natural_height = height_;
}

void CustomToolButton::get_preferred_height_for_width_vfunc(int /* width */, int& minimum_height,
    int& natural_height) const {
  minimum_height = height_;
  natural_height = height_;
}
