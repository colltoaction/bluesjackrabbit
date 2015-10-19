#ifndef BLUESJACKRABBIT_CLIENT_RENDERER_H
#define BLUESJACKRABBIT_CLIENT_RENDERER_H


#include "Transform.h"

class Renderer {
 public:
    Renderer(Transform const& transform);
    void Render(const Cairo::RefPtr <Cairo::Context> &cr);

 private:
    Transform const& transform;
};


#endif  // BLUESJACKRABBIT_CLIENT_RENDERER_H
