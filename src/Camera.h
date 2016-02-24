/*======================================================================

 Copyright (C) 2010-2015. Mario Rincon-Nigro.

 This is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This software is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this software.  If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

#pragma once

#include <OrthoBasis.h>
#include <Vec.h>

class Camera {
public:
    Camera() : m_eye(Vec3f(0.0f, 0.0f, 0.0f)),
	       m_gaze(Vec3f(0.0f, 0.0f, -1.0f)),
	       m_up(Vec3f(0.0f, 1.0f, 0.0f)),
	       m_width(1.0f), m_height(1.0f),
	       m_distance(1.0f) {
	init();
    }
    
    Camera(const Vec3f &eye, const Vec3f &gaze, const Vec3f &up,
	   float width = 1.0, float height = 1.0, float distance = 2.0) :
	m_eye(eye), m_gaze(gaze), m_up(up), m_width(width),
	m_height(height), m_distance(distance) {
	init();
    }
    
    Camera(const Camera &other){
	(*this) = other;
    }
    
    void operator=(const Camera &other){
	m_eye = other.m_eye;
	m_gaze = other.m_gaze;
	m_up = other.m_up;
	m_corner = other.m_corner;
	
	m_width = other.m_width;
	m_height = other.m_height;
	m_distance = other.m_distance;
	
	m_onb = other.m_onb;
    }
    
    Vec3f getEye() const {
	return m_eye;
    }
    
    Vec3f getGaze() const {
	return m_gaze;
    }
    
    Vec3f getUp() const {
	return m_up;
    }
    
    Vec3f getCorner() const {
	return m_corner;
    }
    
    float getWidth() const {
	return m_width;
    }
    
    float getHeight() const {
	return m_height;
    }
    
    float getDistance() const {
	return m_distance;
    }
    
    OrthoBasis getOrthoBasis() const {
	return m_onb;
    }
    
    Vec3f screenToWorld(float x, float y) const {
	return m_corner + m_onb.getU() * x * m_width
	    + m_onb.getV() * y * m_height;
    }
    
private:
    void init() {
	m_onb.initFromWV((m_eye - m_gaze).normalize(), m_up.normalize());
	m_corner = m_eye - m_onb.getW() * m_distance
	    - m_onb.getV() * 0.5 * m_height
	    - m_onb.getU() * 0.5 * m_width;
    }
    
private:
    Vec3f m_eye;
    Vec3f m_gaze;
    Vec3f m_up;
    Vec3f m_corner;
    float m_width;
    float m_height;
    float m_distance;
    
    OrthoBasis m_onb;
};
