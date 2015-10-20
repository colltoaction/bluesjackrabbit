#include "GameObject.h"

::Transform &GameObject::Transform() {
    return transform;
}

::Renderer &GameObject::Renderer() {
    return renderer;
}
