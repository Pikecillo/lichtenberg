#pragma once

#include <Types.h>

class Traceable {
public:
    virtual bool hit(const Ray &r, float tmin, float tmax, Hit &h) const = 0;
};
