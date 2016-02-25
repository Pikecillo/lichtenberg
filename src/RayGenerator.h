
#pragma once

#include <vector>

#include <Camera.h>
#include <Vec.h>

struct Ray {
    Vec3f m_origin;
    Vec3f m_direction;
};

typedef std::vector<Ray> RayBuffer;

class RayGenerator {

public:
    /*
     * Eye rays (primary rays).
     * w and h specify the size of the frame buffer
     */
    static void primary(const Camera &camera,
			int w, int h, RayBuffer &rays);
};
