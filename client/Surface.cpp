#include <iostream>
#include "Surface.h"

Surface::Surface() {
    centro_x = 0.5;
    centro_y = 0.5;
}

Surface::~Surface() {
}

void Surface::Mover(Event const &event, int x, int y) {
    double step = static_cast<double>(event.TimeDelta()) / 1000000000;
    centro_x += x * step;
    centro_y += y * step;
    queue_draw();
}

void Surface::MoverArriba(Event const &event) {
    Mover(event, 0, -1);
}

void Surface::MoverAbajo(Event const &event) {
    Mover(event, 0, 1);
}

void Surface::MoverIzquierda(Event const &event) {
    Mover(event, -1, 0);
}

void Surface::MoverDerecha(Event const &event) {
    Mover(event, 1, 0);
}
