#include <cairomm/context.h>
#include "Renderer.h"

Renderer::Renderer(Transform const &transform)
        : transform(transform) {
}

void Renderer::Render(const Cairo::RefPtr <Cairo::Context> &cr) {
    cr->set_source_rgb(0.86, 0.85, 0.47);
    // draw a circle in the center of the image
    cr->arc(transform.Center().X() * transform.Width(),
            transform.Center().Y() * transform.Height(),
            transform.Height() / 4,
            0.0,
            2.0 * M_PI);
    cr->stroke();
}
