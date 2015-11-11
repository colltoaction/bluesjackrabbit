#include <string>
#include "GameObjectTemplate.h"
#include "CircleCollider.h"
#include "RectangleCollider.h"

template<class BodyType, class ColliderType>
GameObjectTemplate<BodyType, ColliderType>::GameObjectTemplate(const Vector &position)
    : transform_(position)
    , rigid_body_(&transform_)
    , collider_(transform_, rigid_body_) {
}

template<class BodyType, class ColliderType>
const ::Transform &GameObjectTemplate<BodyType, ColliderType>::transform() const {
  return transform_;
}

template<class BodyType, class ColliderType>
Body &GameObjectTemplate<BodyType, ColliderType>::rigid_body() {
  return rigid_body_;
}

template<class BodyType, class ColliderType>
const Collider &GameObjectTemplate<BodyType, ColliderType>::collider() const {
  return collider_;
}

template<class BodyType, class ColliderType>
void GameObjectTemplate<BodyType, ColliderType>::update_fixed() {
}

// See: http://stackoverflow.com/q/8752837
template class GameObjectTemplate<RigidBody, CircleCollider>;
template class GameObjectTemplate<RigidBody, RectangleCollider>;
template class GameObjectTemplate<StaticBody, CircleCollider>;
template class GameObjectTemplate<StaticBody, RectangleCollider>;
