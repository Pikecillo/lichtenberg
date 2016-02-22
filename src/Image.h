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

#include <iostream>
#include <vector>

#include <Vec.h>

class Image {
public:
    Image();

    Image(int width, int height);

    Image(int width, int height, const Vec3f &bg_color);

    int height();

    int width();

    void set(int x, int y, const Vec3f &color);

    void write_ppm(std::ostream &out);

private:
    std::vector<Vec3f> m_pixels;
    int m_width;
    int m_height;
};
