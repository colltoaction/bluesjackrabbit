// TODO(Diego): incluir solamente lo que se usa
#include <gtkmm.h>
#include <iostream>
#include "Editor.h"
#define RC_OK 0
#define RC_ERR_WINDOW 1;

int main(int argc, char **argv) try {
  int ret_code = RC_OK;
  Glib::RefPtr<Gtk::Application> app =
      Gtk::Application::create(argc, argv, "ar.uba.fi.tallerprog.blues.editor");

  Editor editor;

  ret_code = app->run(editor);
  return ret_code;
} catch(const Glib::FileError& ex) {
  std::cerr << "FileError: " << ex.what() << std::endl;
  return RC_ERR_WINDOW;
} catch(const Glib::MarkupError& ex) {
  std::cerr << "MarkupError: " << ex.what() << std::endl;
  return RC_ERR_WINDOW;
} catch(const Gtk::BuilderError& ex) {
  std::cerr << "BuilderError: " << ex.what() << std::endl;
  return RC_ERR_WINDOW;
}
