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
    static float perlin(float x, float y = 0.5f, float z = 0.5f);

    static float turbulence(int octaves,
			    float x, float y = 0.5f, float z = 0.5f);
    
    static float marble(int octaves, float freq,
			float x, float y = 0.5f, float z = 0.5f);

private:
    static float smooth(float t);

    static float lerp(float a, float b, float s);

    static float dotGrad(int g, float u, float v, float w);

    static int hash(int i, int j, int k);

private:
    static const float m_grad[][3];

    static const int m_perm[256];
};

inline float Noise::smooth(float t) {
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

inline float Noise::lerp(float v0, float v1, float s) {
    return v0 + s * (v1 - v0);
}
