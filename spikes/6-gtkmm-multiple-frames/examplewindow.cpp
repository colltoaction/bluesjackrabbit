#include <iostream>
#include "examplewindow.h"
#include "packbox.h"

ExampleWindow::ExampleWindow() : b1("B1"), b2("B2"), b3("Boton 3") {
    dosBotones.add(b1);
    dosBotones.add(b2);
    b1.signal_clicked().connect(
            sigc::mem_fun(*this, &ExampleWindow::on_button_clicked));

    unBoton.add(b3);
    b3.signal_clicked().connect(
            sigc::mem_fun(*this, &ExampleWindow::poner_otro));

    b2.signal_clicked().connect(
            sigc::mem_fun(*this, &ExampleWindow::imprimir));

    mainFrame.add(dosBotones);
    mainFrame.add(unBoton);

    add(mainFrame);
    show_all();
    unBoton.hide();
}

ExampleWindow::~ExampleWindow() {
}

void ExampleWindow::poner_otro() {
    dosBotones.show();
    unBoton.hide();
}

void ExampleWindow::on_button_clicked() {
    dosBotones.hide();
    unBoton.show();
}

void ExampleWindow::imprimir() {
    std::cout << "BOTON 2 CLICKEADO\n";
}
