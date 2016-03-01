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

class Noise {
public:
    Noise();

    Noise(float scale);
    
    void set_scale(float scale);

    float perlin(float x, float y = 0.5f, float z = 0.5f) const;
    
    float turbulence(int octaves, float x, float y = 0.5f,
		     float z = 0.5f) const;
    
    float marble(int octaves, float freq,
		 float x, float y = 0.5f, float z = 0.5f) const;
    
private:
    float smooth(float t) const;

    float lerp(float a, float b, float s) const;

    float dotGrad(int g, float u, float v, float w) const;

    int hash(int i, int j, int k) const;

private:
    float m_scale;

    static const float m_grad[][3];

    static const int m_perm[256];
};

inline Noise::Noise() : m_scale(1.0f) {}

inline Noise::Noise(float scale) : m_scale(scale) {}

inline void Noise::set_scale(float scale) {
    m_scale = scale;
}

inline float Noise::smooth(float t) const {
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

inline float Noise::lerp(float v0, float v1, float s) const {
    return v0 + s * (v1 - v0);
}
