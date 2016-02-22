/**
 * Adapted from Realistic Ray-Tracing. P. Shirley
 */

#pragma once

#include <Vec.h>

class Noise {
public:
    Noise();
    
    float noise(const Vec3f &v) const;
    
    float turbulence(const Vec3f &v, int depth) const;
    
    float dturbulence(const Vec3f &v, int depth, float d) const;
    
    float omega(float t) const;
    
    Vec3f gamma(int i, int j, int k) const;
    
    int int_gamma(int i, int j, int k) const;
    
    float knot(int i, int j, int k, Vec3f &v) const;

private:
    Vec3f m_grad[16];

    int m_phi[16];
};

inline float Noise::omega(float t) const {
    float t2, t3;
    
    t = (t > 0.0f) ? t : -t;
    t2 = t * t;
    t3 = t2 * t;
    
    return (-6.0f * t3 * t3 + 15.0f * t2 * t2 - 10.0f * t2 * t + 1.0f);
}

inline Vec3f Noise::gamma(int i, int j, int k) const {
    int idx;
    
    idx = m_phi[abs(k) % 16];
    idx = m_phi[abs(j + idx) % 16];
    idx = m_phi[abs(i + idx) % 16];
    
    return m_grad[idx];
}

inline float Noise::knot(int i, int j, int k, Vec3f &v) const {
    return omega(v.x()) * omega(v.y()) * omega(v.z()) * gamma(i, j, k).dot(v);
}
