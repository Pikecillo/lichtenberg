#include <math.h>

#include <Sphere.h>

bool Sphere::hit(const Ray &r, float tmin, float tmax, Hit &h) const {
    Vec3f temp = r.m_origin - m_center;

    double a = r.m_direction.dot(r.m_direction);
    double b = 2 * r.m_direction.dot(temp);
    double c = temp.dot(temp) - m_radius * m_radius;
    
    double discriminant = b * b - 4 * a * c;
    
    // If ray instersects sphere
    if(discriminant > 0) {
	discriminant = sqrt(discriminant);
	
	double t = (-b - discriminant) / (2 * a);
	
	if(t < tmin)
	    t = (-b + discriminant) / (2 * a);
	
	if(t < tmin || t > tmax)
	    return false;
	
	h.t = t;
	h.normal = (r.m_origin + r.m_direction * t - m_center);
	h.normal = h.normal.normalize();
	
	return true;
    }
    
    return false;
}
