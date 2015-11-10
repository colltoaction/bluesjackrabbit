#include <string>
#include "GameObjectTemplate.h"

template<class BodyType>
GameObjectTemplate<BodyType>::GameObjectTemplate(const Vector &position)
    : transform_(position)
    , rigid_body_(&transform_)
    , collider_(transform_, rigid_body_) {
}

template<class BodyType>
const ::Transform &GameObjectTemplate<BodyType>::transform() const {
  return transform_;
}

template<class BodyType>
Body &GameObjectTemplate<BodyType>::rigid_body() {
  return rigid_body_;
}

template<class BodyType>
const Collider &GameObjectTemplate<BodyType>::collider() const {
  return collider_;
}

template<class BodyType>
std::string GameObjectTemplate<BodyType>::type() const {
  return "circulo";
}

template<class BodyType>
void GameObjectTemplate<BodyType>::update_fixed() {
}

// See: http://stackoverflow.com/q/8752837
template class GameObjectTemplate<RigidBody>;
template class GameObjectTemplate<StaticBody>;
