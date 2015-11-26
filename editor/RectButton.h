#ifndef BLUESJACKRABBIT_EDITOR_RECTBUTTON_H
#define BLUESJACKRABBIT_EDITOR_RECTBUTTON_H
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>
#include "CustomToolButton.h"

class RectButton : public CustomToolButton {
public:
  RectButton(const Glib::ustring& label, int width = 64, int height = 64);
  
private:

  class RectIconWidget : public Gtk::DrawingArea {
  public:
    RectIconWidget(int width, int height);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  private:
    int width_;
    int height_;
  };

  RectIconWidget icon_;
};

#endif // BLUESJACKRABBIT_EDITOR_RECTBUTTON_H