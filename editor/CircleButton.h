#ifndef BLUESJACKRABBIT_EDITOR_CIRCLEBUTTON_H
#define BLUESJACKRABBIT_EDITOR_CIRCLEBUTTON_H
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "CustomToolButton.h"

class CircleButton : public CustomToolButton {
public:
  CircleButton(const Glib::ustring& label, int width = 64, int height = 64);

private:

  class CircleIconWidget : public Gtk::DrawingArea {
  public:
    CircleIconWidget(int width, int height);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  private:
    int width_;
    int height_;
  };

  CircleIconWidget icon_;
};

#endif // BLUESJACKRABBIT_EDITOR_CIRCLEBUTTON_H