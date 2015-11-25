#ifndef BLUESJACKRABBIT_EDITOR_CUSTOMBUTTON_H
#define BLUESJACKRABBIT_EDITOR_CUSTOMBUTTON_H
#include <cairomm/context.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/widget.h>

class CustomToolButton : public Gtk::ToolButton {
public:
  CustomToolButton(const Glib::ustring& label, int width = 64, int height = 64);
  virtual void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const;
  virtual void get_preferred_width_for_height_vfunc(int /* height */, int& minimum_width,
      int& natural_width) const;
  virtual void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const;
  virtual void get_preferred_height_for_width_vfunc(int /* width */, int& minimum_height,
      int& natural_height) const;
  virtual ~CustomToolButton() {}

private:
  int width_;
  int height_;
};

#endif // BLUESJACKRABBIT_EDITOR_CUSTOMBUTTON_H