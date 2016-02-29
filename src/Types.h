#pragma once

#include <vector>

#include <Vec.h>

struct Ray {
    Vec3f m_origin;
    Vec3f m_direction;
};

struct Hit {
    float t;
    Vec3f normal;
};

typedef std::vector<Ray> RayBuffer;
typedef std::vector<Hit> HitBuffer;

