#include <Tracer.h>

HitBuffer Tracer::trace(const RayBuffer &rays,
			const Traceable *traceable) {
    HitBuffer hits(rays.size());

    for(int i = 0; i < rays.size(); i++) {
	traceable->hit(rays[i], 0.001f, 1000.0f, hits[i]);
    }

    return hits;
}
