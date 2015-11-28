#ifndef BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <goocanvasmm/item.h>

class LevelObject {
public:
  LevelObject(Glib::RefPtr<Goocanvas::Item> representation);
  virtual ~LevelObject() {}
  std::vector<std::pair<std::string, std::string> > metadata();
  void set_property(std::string property, std::string value);
  const Glib::RefPtr<Goocanvas::Item> representation() {return representation_;}

private:
  std::map<std::string, std::string> metadata_;
  Glib::RefPtr<Goocanvas::Item> representation_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
