#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "CircleButton.h"

#include <iostream>

CircleButton::CircleButton(const Glib::ustring& label, int width, int height)
    : Gtk::ToolButton(label), width_(width), height_(height), icon_(width, height) {
  set_icon_widget(icon_);
}

void CircleButton::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const {
  minimum_width = width_;
  natural_width = width_;
}

void CircleButton::get_preferred_width_for_height_vfunc(int /* height */, int& minimum_width,
    int& natural_width) const {
  minimum_width = width_;
  natural_width = width_;
}

void CircleButton::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const {
  minimum_height = height_;
  natural_height = height_;
}

void CircleButton::get_preferred_height_for_width_vfunc(int /* width */, int& minimum_height,
    int& natural_height) const {
  minimum_height = height_;
  natural_height = height_;
}

CircleButton::CircleIconWidget::CircleIconWidget(int width, int height) : width_(width),
    height_(height) {
}

bool CircleButton::CircleIconWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  cr->save();

  Gdk::RGBA backgrnd_color = get_style_context()->get_background_color();
  cr->set_source_rgba(backgrnd_color.get_red(), backgrnd_color.get_green(),
      backgrnd_color.get_blue(), backgrnd_color.get_alpha());
  cr->paint();

  cr->set_source_rgba(0.0, 0.0, 1.0, 1.0);
  int real_width = get_allocated_width();
  int real_height = get_allocated_height();
  double center_x = (width_ > real_width ? width_ : real_width) / 2.0;
  double center_y = (height_ > real_height ? height_ : real_height) / 2.0;
  double radius = (width_ < height_ ? width_ : height_) / 2.0;
  cr->arc(center_x, center_y, radius, 0, 2 * M_PI);
  cr->fill();

  cr->restore();
  return true;
}
