#pragma once

#include <vector>

#include <Camera.h>
#include <Types.h>
#include <Vec.h>

class RayGenerator {

public:
    /*
     * Eye rays (primary rays).
     * w and h specify the size of the frame buffer
     */
    static void primary(const Camera &camera,
			int w, int h, RayBuffer &rays);
};
