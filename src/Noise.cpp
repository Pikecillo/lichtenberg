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
    {0.0, 1.0, 1.0}, { 0.0,-1.0, 1.0}, {0.0, 1.0,-1.0}, { 0.0,-1.0,-1.0},
    {1.0, 1.0, 0.0}, {-1.0, 1.0, 0.0}, {0.0,-1.0, 1.0}, { 0.0,-1.0,-1.0} 
};

const int Noise::m_perm[] = {
    135, 198,  26, 205, 110,  93, 250, 210, 138,  53,  96,  27,  78,  25,
      1, 211,  41,  89, 233,   4, 156, 146, 253,  98, 232, 115, 155,  39,
    157, 247,  76, 203, 238,  72, 221,  69,  21,  24,   3, 107,  32,  11,
    178, 229,  66,  38, 102, 189, 187, 126, 220,  34, 133,  33,  23, 116,
     37,  83,  70,  80, 131, 136, 114, 179, 183, 193, 166, 234, 213, 113,
    245, 143,  20, 215, 218, 226,  52,  40, 153,  61, 201,  22,  13, 104,
     77,  97, 194,  67, 109, 117, 190, 230,  15, 212, 160, 244, 204, 231,
     51, 177,  18,   9, 181, 149,  75,   7, 106, 239, 134, 111, 125, 150,
     99, 191, 128, 154,  64,  31, 152,  60,  82, 141, 162, 108, 242, 164,
     56, 216, 122, 147, 185, 240, 186,  36, 151, 243,  46,  62, 123, 246,
     42, 172,  49, 140, 145, 161, 254, 127,  50,  12, 100, 168, 175,  92,
     43,  58,  90, 132, 124,  45,  44, 180,   6, 255, 184, 182,  28,  71,
    241,  88, 249,  85, 118, 171,  17,  65, 148,  74,  73, 188,  14,  91,
    223, 197,   2,  59,  30, 112, 130, 214, 202, 173, 236,  47,  16, 167,
      0, 222,  68, 105, 195,  84, 208, 119, 207, 139,  48, 209, 120, 251,
    248, 170,  95,  63, 227, 103, 200, 163,  87, 121, 225, 219, 137, 174,
     54, 228,  86,  19,   8, 192, 237,  79, 129, 144, 169, 252,   5, 199,
     57, 224, 176,  35,  29, 206,  10, 101, 217, 158,  55,  94, 235, 165,
    196,  81, 159, 142
};

float Noise::dotGrad(int h, float x, float y, float z) {
    return (m_grad[h][0] * x + m_grad[h][1] * y + m_grad[h][2] * z);
}

int Noise::hash(int i, int j, int k) {
    // TODO: Simplify this. We just need a way of handling modulo
    // with negative integers so that the cycles are consistent with
    // the positive numbers.
    i = i < 0 ? ((i - 1) & 0xFF + 256) & 0xFF : i & 0xFF;
    j = j < 0 ? ((j - 1) & 0xFF + 256) & 0xFF : j & 0xFF;
    k = k < 0 ? ((k - 1) & 0xFF + 256) & 0xFF : k & 0xFF;

    return m_perm[(k + m_perm[(j + m_perm[i]) & 0xFF]) & 0xFF] & 0xF;
}

/**
 * Improved Perlin noise.
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @param z z-coordinate
 * @return A pseudo-random real number in the range [-1.0, 0.0]
 */
float Noise::perlin(float x, float y, float z) {
    int i = static_cast<int>(floor(x));
    int j = static_cast<int>(floor(y));
    int k = static_cast<int>(floor(z));   

    float u = smooth(x -= floor(x));
    float v = smooth(y -= floor(y));
    float w = smooth(z -= floor(z));

    int h0 = hash(i, j, k);
    int h1 = hash(i, j, k + 1);
    int h2 = hash(i, j + 1, k);
    int h3 = hash(i, j + 1, k + 1);
    int h4 = hash(i + 1, j, k);
    int h5 = hash(i + 1, j, k + 1);
    int h6 = hash(i + 1, j + 1, k);
    int h7 = hash(i + 1, j + 1, k + 1);

    float g0 = dotGrad(h0, x, y, z);
    float g1 = dotGrad(h1, x, y, z - 1.0);
    float g2 = dotGrad(h2, x, y - 1.0, z);
    float g3 = dotGrad(h3, x, y - 1.0, z - 1.0);
    float g4 = dotGrad(h4, x - 1.0, y, z);
    float g5 = dotGrad(h5, x - 1.0, y, z - 1.0);
    float g6 = dotGrad(h6, x - 1.0, y - 1.0, z);
    float g7 = dotGrad(h7, x - 1.0, y - 1.0, z - 1.0);
    
    return lerp(lerp(lerp(g0, g1, w), lerp(g2, g3, w), v),
		lerp(lerp(g4, g5, w), lerp(g6, g7, w), v), u);
}

float Noise::turbulence(int octaves, float x, float y, float z) {
    float t = 0.0;
    float freq = 1.0;

    for(int i = 1; i <= octaves; i++) {
	t += fabs(perlin(x * freq, y * freq, z * freq) / freq);
	freq *= 2.0;
    }

    return t;
}

float Noise::marble(int octaves, float freq, float x, float y, float z) {
    return fabs(sin(freq * x + turbulence(octaves, x, y, z)));
}
