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

#include <math.h>
#include <stdlib.h>

#include <Noise.h>

const float Noise::m_grad[][3] = {
    {1.0, 1.0, 0.0}, {-1.0, 1.0, 0.0}, {1.0,-1.0, 0.0}, {-1.0,-1.0, 0.0},
    {1.0, 0.0, 1.0}, {-1.0, 0.0, 1.0}, {1.0, 0.0,-1.0}, {-1.0, 0.0,-1.0},
    {0.0, 1.0, 1.0}, { 0.0,-1.0, 1.0}, {0.0, 1.0,-1.0}, { 0.0,-1.0,-1.0}
};

const int Noise::m_perm[] = {
    10, 5, 6, 7, 9, 8, 1, 0, 4, 2, 3, 11
};

float Noise::dotGrad(int g, float u, float v, float w) {
    return m_grad[g][0] * u + m_grad[g][1] * v + m_grad[g][2] * w;
}

int Noise::hash(int i, int j, int k) {
    return m_perm[(k + m_perm[(j + m_perm[i]) % 12]) % 12];
}

float Noise::eval(float x, float y, float z) {
    int i = x;
    int j = y;
    int k = z;
    float u = smooth(x - i);
    float v = smooth(y - j);
    float w = smooth(z - k);

    int h0 = hash(i, j, k);
    int h1 = hash(i, j, k + 1);
    int h2 = hash(i, j + 1, k);
    int h3 = hash(i, j + 1, k + 1);
    int h4 = hash(i + 1, j, k);
    int h5 = hash(i + 1, j, k + 1);
    int h6 = hash(i + 1, j + 1, k);
    int h7 = hash(i + 1, j + 1, k + 1);

    float g0 = dotGrad(m_perm[h0], u, v, w);
    float g1 = dotGrad(m_perm[h1], u, v, w - 1.0);
    float g2 = dotGrad(m_perm[h2], u, v - 1.0, w);
    float g3 = dotGrad(m_perm[h3], u, v - 1.0, w - 1.0);
    float g4 = dotGrad(m_perm[h4], u - 1.0, v, w);
    float g5 = dotGrad(m_perm[h5], u - 1.0, v, w - 1.0);
    float g6 = dotGrad(m_perm[h6], u - 1.0, v - 1.0, w);
    float g7 = dotGrad(m_perm[h7], u - 1.0, v - 1.0, w - 1.0);
    
    return lerp(lerp(lerp(g0, g1, w), lerp(g2, g3, w), v),
		lerp(lerp(g4, g5, w), lerp(g6, g7, w), v), u);
}
