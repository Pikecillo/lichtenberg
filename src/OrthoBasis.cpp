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

#include <OrthoBasis.h>

#define ONB_EPSILON 0.01f

/*
 * Initialize orthonormal basis from provided u vector
 */
void OrthoBasis::initFromU(const Vec3f &u){
    Vec3f x(1.0f, 0.0f, 0.0f);
    Vec3f y(0.0f, 1.0f, 0.0f);
    
    m_u = u.normalize();
    m_v = m_u.cross(x);
    
    // Just in case u and n have almost the same direction
    if(m_v.length() < ONB_EPSILON)
	m_v = m_u.cross(y);
    
    m_w = m_u.cross(m_v);
}

/*
 * Initialize orthonormal basis from provided v vector
 */
void OrthoBasis::initFromV(const Vec3f &v){
    Vec3f x(1.0f, 0.0f, 0.0f);
    Vec3f y(0.0f, 1.0f, 0.0f);
    
    m_v = v.normalize();
    m_u = m_v.cross(x);
    
    if(m_u.length() < ONB_EPSILON)
	m_u = m_v.cross(y);
    
    m_w = m_u.cross(m_v);
}

/*
 * Initialize orthonormal basis from provided w vector
 */
void OrthoBasis::initFromW(const Vec3f &w){
    Vec3f x(1.0f, 0.0f, 0.0f);
    Vec3f y(0.0f, 1.0f, 0.0f);
    
    m_w = w.normalize();
    m_u = w.cross(x);
    
    if(m_u.length() < ONB_EPSILON)
	m_u = m_w.cross(y);
    
    m_v = m_w.cross(m_u);
}

/*
 * Initialize orthonormal basis from provided u and v vectors.
 * Always keep direction of u
 */
void OrthoBasis::initFromUV(const Vec3f &u, const Vec3f &v){
    m_u = u.normalize();
    m_w = m_u.cross(m_v).normalize();
    m_v = m_w.cross(m_u).normalize();
}

/*
 * Initialize orthonormal basis from provided u and v vectors.
 * Always keep direction of v
 */
void OrthoBasis::initFromVU(const Vec3f &v, const Vec3f &u){
    m_v = v.normalize();
    m_w = u.cross(m_v).normalize();
    m_u = m_v.cross(m_w).normalize();
}

/*
 * Initialize orthonormal basis from provided u and v vectors.
 * Always keep direction of u
 */
void OrthoBasis::initFromUW(const Vec3f &u, const Vec3f &w){
    m_u = u.normalize();
    m_v = w.cross(m_u).normalize();
    m_w = m_u.cross(m_v).normalize();
}

/*
 * Initialize orthonormal basis from provided u and v vectors.
 * Always keep direction of w
 */
void OrthoBasis::initFromWU(const Vec3f &w, const Vec3f &u){
    m_w = w.normalize();
    m_v = m_w.cross(u).normalize();
    m_u = m_v.cross(m_v).normalize();
}

/*
 * Initialize orthonormal basis from provided u and v vectors.
 * Always keep direction of v
 */
void OrthoBasis::initFromVW(const Vec3f &v, const Vec3f &w){
    m_v = v.normalize();
    m_u = m_v.cross(w).normalize();
    m_w = m_u.cross(m_v).normalize();
}

/*
 * Initialize orthonormal basis from provided u and v vectors.
 * Always keep direction of w
 */
void OrthoBasis::initFromWV(const Vec3f &w, const Vec3f &v){
    m_w = w.normalize();
    m_u = v.cross(m_w).normalize();
    m_v = m_w.cross(m_u).normalize();
}

/*
 * Equality comparison operator
 */
bool OrthoBasis::operator==(const OrthoBasis &other) const {
    return (m_u == other.m_u &&
	    m_v == other.m_v &&
	    m_w == other.m_w);
}
