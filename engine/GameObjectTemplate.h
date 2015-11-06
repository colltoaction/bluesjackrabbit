#ifndef BLUESJACKRABBIT_ENGINE_GAMEOBJECTTEMPLATE_H
#define BLUESJACKRABBIT_ENGINE_GAMEOBJECTTEMPLATE_H


#include <string>
#include "Body.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "RigidBody.h"
#include "StaticBody.h"


template<class BodyType>
class GameObjectTemplate : public GameObject {
 public:
  explicit GameObjectTemplate(const Vector &position);
  virtual const Transform &transform() const;
  virtual Body &rigid_body();
  virtual std::string type() const;
  virtual void update_fixed();

 protected:
  virtual const Collider &collider() const;

 private:
  Transform transform_;
  BodyType rigid_body_;
  Collider collider_;
};

template class GameObjectTemplate<RigidBody>;
template class GameObjectTemplate<StaticBody>;


#endif  // BLUESJACKRABBIT_ENGINE_GAMEOBJECTTEMPLATE_H
