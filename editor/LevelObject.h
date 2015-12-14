#ifndef BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
#define BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
#include <map>
#include <utility>
#include <string>
#include <vector>
#include "CanvasItem.h"
#include "LevelObjectType.h"

class LevelObject {
public:
  LevelObject(double x, double y, const CanvasItem &representation);
  virtual ~LevelObject() {}
  virtual LevelObjectType object_type() const = 0;

  double x() const;
  double y() const;
  void set_x(double x);
  void set_y(double y);

  std::vector<std::pair<std::string, std::string> > metadata();
  void set_property(std::string property, std::string value);
  const CanvasItem* representation() const {return representation_;}

private:
  double x_;
  double y_;
  std::map<std::string, std::string> metadata_;
  const CanvasItem* representation_;
};

#endif // BLUESJACKRABBIT_EDITOR_LEVELOBJECT_H
