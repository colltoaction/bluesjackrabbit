#ifndef BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
#include <map>
#include <utility>
#include <string>
#include <vector>
#include <goocanvasmm/item.h>
#include "LevelObjectType.h"

class LevelObject {
public:
  LevelObject(double x, double y, Glib::RefPtr<Goocanvas::Item> &representation);
  virtual ~LevelObject() {}
  virtual LevelObjectType object_type() const = 0;

  double x() const;
  double y() const;

  std::vector<std::pair<std::string, std::string> > metadata();
  void set_property(std::string property, std::string value);
  Glib::RefPtr<Goocanvas::Item>* representation() const {return representation_;}

private:
  double x_;
  double y_;
  std::map<std::string, std::string> metadata_;
  Glib::RefPtr<Goocanvas::Item>* representation_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
