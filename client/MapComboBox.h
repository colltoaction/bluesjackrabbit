#ifndef MAPCOMBOBOX_H_
#define MAPCOMBOBOX_H_

#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/builder.h>

class MapComboBox : public Gtk::ComboBox {
 public:
  MapComboBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
  virtual ~MapComboBox();

  // Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord {
   public:
      ModelColumns() {
        add(m_col_id);
        add(m_col_name);
      }

      Gtk::TreeModelColumn<int> m_col_id;
      Gtk::TreeModelColumn<Glib::ustring> m_col_name;
  };

  ModelColumns m_Columns;

  // Child widgets:
  Gtk::ComboBox m_Combo;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
};

#endif /* MAPCOMBOBOX_H_ */
