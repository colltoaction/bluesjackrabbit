#include "MapComboBox.h"

#include <iostream>

MapComboBox::MapComboBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) {
  if (cobject == NULL && (&refGlade) == NULL) {
    std::cout << "entro...\n";
  }
  std::cout << "Se llama esto?\n";
  // Create the Tree model:
    // m_refTreeModel = Gtk::TreeStore::create(m_Columns);
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    set_model(m_refTreeModel);

    // Fill the ComboBox's Tree Model:
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 1;
    row[m_Columns.m_col_name] = "Billy Bob";
    set_active(row);

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 2;
    row[m_Columns.m_col_name] = "Joey Jojo";

    row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = 3;
    row[m_Columns.m_col_name] = "Rob McRoberts";

    // Add the model columns to the Combo (which is a kind of view),
    // rendering them in the default way:
    pack_start(m_Columns.m_col_id);
    pack_start(m_Columns.m_col_name);

    show_all_children();
}

MapComboBox::~MapComboBox() {
}

