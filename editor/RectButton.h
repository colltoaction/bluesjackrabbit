#ifndef BLUESJACKRABBIT_EDITOR_RECTBUTTON_H
#define BLUESJACKRABBIT_EDITOR_RECTBUTTON_H
#include <cairomm/context.h>
#include <gtkmm/toolbutton.h>

class RectButton : public Gtk::ToolButton {
public:
  RectButton(const Glib::ustring& label, int width = 64, int height = 64);
  void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const;
  void get_preferred_width_for_height_vfunc(int /* height */, int& minimum_width,
      int& natural_width) const;
  void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const;
  void get_preferred_height_for_width_vfunc(int /* width */, int& minimum_height,
      int& natural_height) const;
private:

  class RectIconWidget : public Gtk::DrawingArea {
  public:
    RectIconWidget(int width, int height);
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  private:
    int width_;
    int height_;
  };

  int width_;
  int height_;
  RectIconWidget icon_;
};

#endif // BLUESJACKRABBIT_EDITOR_RECTBUTTON_H