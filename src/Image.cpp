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

/*
 * This code has been adapted from Realistic Ray-Tracing by P. Shirley
 */

#include <assert.h>

#include <Image.h>

Image::Image() {}

Image::Image(int width, int height){
    m_width = width;
    m_height = height;

    m_pixels.resize(width * height);
}

Image::Image(int width, int height, const Vec3f &bg_color){

    m_width = width;
    m_height = height;

    m_pixels.resize(width * height);

    for(int i = 0 ; i < width * height ; i++){
	m_pixels[i] = bg_color;
    }
}

int Image::height(){
    return m_height;
}

int Image::width(){
    return m_width;
}

void Image::set(int x, int y, const Vec3f &color){
    m_pixels[y * m_width + x] = color;
}

void Image::write_ppm(std::ostream &out){
    // Raw PPM format header
    out << "P6\n"; // Magic number
    out << m_width << " " << m_height << "\n";
    out << "255\n"; // Maximum color value
    
    // Write pixels in row-major order from top to bottom
    for(int i = 0; i < m_pixels.size(); i++) {
	Vec3f pixel = m_pixels[i].clamp(0.0f, 1.0f);

	out.put(static_cast<unsigned char>(255 * pixel[0]));
	out.put(static_cast<unsigned char>(255 * pixel[1]));
	out.put(static_cast<unsigned char>(255 * pixel[2]));
    }
}
