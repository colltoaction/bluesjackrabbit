#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window {
 public:
    ExampleWindow();

    virtual ~ExampleWindow();

 protected:
    // Signal handlers:
    void on_button_clicked();

    void poner_otro();

    void imprimir();

    Gtk::Box mainFrame;
    // Child widgets:
    Gtk::Box dosBotones;
    Gtk::Button b1;
    Gtk::Button b2;

    Gtk::Box unBoton;
    Gtk::Button b3;

 private:
    int vecesB2 = 0;
};

#endif  // GTKMM_EXAMPLEWINDOW_H
