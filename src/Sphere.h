#pragma once

#include <Traceable.h>
#include <Types.h>
#include <Vec.h>

class Sphere : public Traceable {
public:
    Sphere() {}
    
    Sphere(const Sphere &other) {
	m_center = other.m_center;
	m_radius = other.m_radius;
    }
    
    Sphere(Vec3f center, float radius) : m_center(center), m_radius(radius) {}

    bool hit(const Ray &r, float tmin, float tmax, Hit &h) const override;

private:
    Vec3f m_center;
    float m_radius;
};

