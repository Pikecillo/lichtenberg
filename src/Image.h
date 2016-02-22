/**
   Houston, July 2010
   Mario Rincon Nigro
 */

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
