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

#include <Vec.h>

class OrthoBasis {
public:
    OrthoBasis() {};

    OrthoBasis(const Vec3f &a, const Vec3f &b, const Vec3f &c) {
	m_u = a; m_v = b; m_w = c;
    }

    OrthoBasis(const OrthoBasis &other) {
	(*this) = other;
    }

    void operator=(const OrthoBasis &other) {
	m_u = other.m_u; m_v = other.m_v; m_w = other.m_w;
    }

    void set(const Vec3f &a, const Vec3f &b, const Vec3f &c) {
	m_u = a; m_v = b; m_w = c;
    }

    Vec3f getU() const { return m_u; }
    Vec3f getV() const { return m_v; }
    Vec3f getW() const { return m_w; }

    void initFromU(const Vec3f &u);
    void initFromV(const Vec3f &v);
    void initFromW(const Vec3f &w);

    void initFromUV(const Vec3f &u, const Vec3f &v);
    void initFromVU(const Vec3f &v, const Vec3f &u);
    
    void initFromUW(const Vec3f &u, const Vec3f &w);
    void initFromWU(const Vec3f &w, const Vec3f &u);
    
    void initFromVW(const Vec3f &v, const Vec3f &w);
    void initFromWV(const Vec3f &w, const Vec3f &v);
    
    bool operator==(const OrthoBasis &other) const;
    
private:
    Vec3f m_u;
    Vec3f m_v;
    Vec3f m_w;
};
