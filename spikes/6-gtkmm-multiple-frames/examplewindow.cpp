//$Id: examplewindow.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <iostream>
#include "examplewindow.h"
#include "packbox.h"

ExampleWindow::ExampleWindow() : b1("B1"), b2("B2"), b3("Boton 3"){
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

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::poner_otro()
{
  dosBotones.show();
  unBoton.hide();

}

void ExampleWindow::on_button_clicked()
{
  dosBotones.hide();
  unBoton.show();

}

void ExampleWindow::imprimir(){
  std::cout << "BOTON 2 CLICKEADO\n";
}