#pragma once

#include <Traceable.h>
#include <Types.h>

class Tracer {
public:
    static HitBuffer trace(const RayBuffer &rays,
			   const Traceable *traceable);
};
