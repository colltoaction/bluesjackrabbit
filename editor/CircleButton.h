#ifndef BLUESJACKRABBIT_EDITOR_CIRCLEBUTTON_H
#define BLUESJACKRABBIT_EDITOR_CIRCLEBUTTON_H
#include <cairomm/context.h>
#include <gtkmm/toolbutton.h>

class CircleButton : public Gtk::ToolButton {
public:
  CircleButton(const Glib::ustring& label, int width = 64, int height = 64);
  void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const;
  void get_preferred_width_for_height_vfunc(int /* height */, int& minimum_width,
      int& natural_width) const;
  void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const;
  void get_preferred_height_for_width_vfunc(int /* width */, int& minimum_height,
      int& natural_height) const;
  //bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
private:

  class CircleIconWidget : public Gtk::DrawingArea {
  public:
    CircleIconWidget(int width, int height);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  private:
    int width_;
    int height_;
  };

  int width_;
  int height_;
  CircleIconWidget icon_;
};

#endif // BLUESJACKRABBIT_EDITOR_CIRCLEBUTTON_H