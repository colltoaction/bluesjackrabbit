#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "CustomToolButton.h"
#include "RectButton.h"

RectButton::RectButton(const Glib::ustring& label, int width, int height)
    : CustomToolButton(label, width, height), icon_(width, height) {
  set_icon_widget(icon_);
}

RectButton::RectIconWidget::RectIconWidget(int width, int height) : width_(width),
    height_(height) {
}

bool RectButton::RectIconWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  cr->save();

  Gdk::RGBA backgrnd_color = get_style_context()->get_background_color();
  cr->set_source_rgba(backgrnd_color.get_red(), backgrnd_color.get_green(),
      backgrnd_color.get_blue(), backgrnd_color.get_alpha());
  cr->paint();

  cr->set_source_rgba(0.0, 0.0, 1.0, 1.0);
  int real_width = get_allocated_width();
  int real_height = get_allocated_height();
  double x = (width_ > real_width ? 0 : real_width - width_) / 2.0;
  double y = (height_ > real_height ? 0 : real_height - height_) / 2.0;
  cr->rectangle(x, y, width_, height_ / 2.0);
  cr->fill();

  cr->restore();
  return true;
}
