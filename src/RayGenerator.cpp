#include <RayGenerator.h>

void RayGenerator::primary(const Camera &camera,
			   int w, int h, RayBuffer &rays) {
    Vec3f eye = camera.getEye();
    
    for(int i = 0; i < h; i++)
	for(int j = 0; j < w; j++){
	    int index = i * w + j;
	    float x, y;
	    
	    x = (float(index % w) + 0.5f) / float(w);
	    y = (float(index / w) + 0.5f) / float(h);
	    
	    rays[index].m_origin = eye;
	    rays[index].m_direction = (camera.screenToWorld(x, y) -
				       eye).normalize();
	}
}
