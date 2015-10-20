#include <cairomm/context.h>
#include "Renderer.h"

void Renderer::Render(const Cairo::RefPtr<Cairo::Context> &cr, const Transform &transform) {
    cr->set_source_rgb(0.86, 0.85, 0.47);
    // draw a circle in the center of the image
    cr->arc(transform.Position().X() * width,
            transform.Position().Y() * height,
            height / 4,
            0.0,
            2.0 * M_PI);
    cr->stroke();
}
