#pragma once

#include <algorithm>
#include <math.h>

class Vec3f {
public:
    Vec3f(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    
    Vec3f(const Vec3f &other);
    
    const Vec3f &operator=(const Vec3f &other);
    
    float x() const;

    float y() const;

    float z() const;

    float &operator[](int i);

    bool operator==(const Vec3f &other) const;
    
    Vec3f operator+(const Vec3f &other) const;
    
    Vec3f operator-() const;
    
    Vec3f operator-(const Vec3f &other) const;
    
    Vec3f operator*(float s) const;
    
    Vec3f operator*(const Vec3f &other) const;
    
    Vec3f operator/(float s) const;
    
    Vec3f operator/(const Vec3f &other) const;
    
    float dot(const Vec3f &other) const;
    
    float length() const;
    
    Vec3f normalize() const;
    
    Vec3f cross(const Vec3f &other) const;
    
    Vec3f max(const Vec3f &other) const;
    
    Vec3f min(const Vec3f &other) const;
    
    float min() const;
    
    float max() const;

private:
    float m_x, m_y, m_z;
};

inline Vec3f::Vec3f(float x, float y, float z)
	     : m_x(x), m_y(y), m_z(z) {}
    
inline Vec3f::Vec3f(const Vec3f &other) {
    (*this) = other;
}
    
inline const Vec3f &Vec3f::operator=(const Vec3f &other) {
    m_x = other.m_x; m_y = other.m_y; m_z = other.m_z;
    
    return (*this);
}
    
inline float Vec3f::x() const {
    return m_x;
}

inline float Vec3f::y() const {
    return m_y;
}

inline float Vec3f::z() const {
    return m_z;
}
    
inline float &Vec3f::operator[](int i) {
    return *((float *)this + i);
}

inline bool Vec3f::operator==(const Vec3f &other) const {
    return (m_x == other.m_x && m_y == other.m_y && m_z == other.m_z);
}
    
inline Vec3f Vec3f::operator+(const Vec3f &other) const {
    return Vec3f(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}
    
inline Vec3f Vec3f::operator-() const {
    return Vec3f(-m_x, -m_y, -m_z);
}
    
inline Vec3f Vec3f::operator-(const Vec3f &other) const {
    return Vec3f(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}
    
inline Vec3f Vec3f::operator*(float s) const {
    return Vec3f(m_x * s, m_y * s, m_z * s);
}

inline Vec3f Vec3f::operator*(const Vec3f &other) const {
    return Vec3f(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
}
    
inline Vec3f Vec3f::operator/(float s) const {
    return Vec3f(m_x / s, m_y / s, m_z / s);
}

inline Vec3f Vec3f::operator/(const Vec3f &other) const {
    return Vec3f(m_x / other.m_x, m_y / other.m_y, m_z / other.m_z);
}
    
inline float Vec3f::dot(const Vec3f &other) const {
    return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
}

inline float Vec3f::length() const {
    return sqrtf(dot(*this));
}
    
inline Vec3f Vec3f::normalize() const {
    return (*this) / length();
}
    
inline Vec3f Vec3f::cross(const Vec3f &other) const {
    Vec3f res;
    res.m_x = m_y * other.m_z - m_z * other.m_y;
    res.m_y = m_z * other.m_x - m_x * other.m_z;
    res.m_z = m_x * other.m_y - m_y * other.m_x;
    return res;
}

inline Vec3f Vec3f::max(const Vec3f &other) const {
    return Vec3f(m_x < other.m_x ? other.m_x : m_x,
		 m_y < other.m_y ? other.m_y : m_y,
		 m_z < other.m_z ? other.m_z : m_z);
}

inline Vec3f Vec3f::min(const Vec3f &other) const {
    return Vec3f(m_x >= other.m_x ? other.m_x : m_x,
		 m_y >= other.m_y ? other.m_y : m_y,
		 m_z >= other.m_z ? other.m_z : m_z);
}

inline float Vec3f::min() const {
    return std::min(m_x, std::min(m_y, m_z));
}

inline float Vec3f::max() const {
    return std::max(m_x, std::max(m_y, m_z));
}
