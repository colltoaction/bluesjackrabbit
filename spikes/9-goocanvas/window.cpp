/* Copyright (C) 2008 The goocanvasmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "window.h"
#include "primitives.h"

DemoWindow::DemoWindow()
{
  set_title("goocanvasmm Demo");
  set_default_size(640, 600);

  _pages.push_back(new Primitives());


  auto nb = Gtk::manage(new Gtk::Notebook());

  for(const auto& p : _pages)
  {
    nb->append_page(*(p->getWidget()), p->getName());
  }

  add(*nb);
  show_all_children();
}

