#include <math.h>
#include <stdlib.h>

#include <Noise.h>

Noise::Noise() {
    m_grad[0] = Vec3f(1.0, 1.0, 0.0);
    m_grad[1] = Vec3f(-1.0, 1.0, 0.0);
    m_grad[2] = Vec3f(1.0,-1.0, 0.0);
    m_grad[3] = Vec3f(-1.0,-1.0, 0.0);
    
    m_grad[4] = Vec3f(1.0, 0.0, 1.0);
    m_grad[5] = Vec3f(-1.0, 0.0, 1.0);
    m_grad[6] = Vec3f(1.0, 0.0,-1.0);
    m_grad[7] = Vec3f(-1.0, 0.0,-1.0);
    
    m_grad[8] = Vec3f(0.0, 1.0, 1.0);
    m_grad[9] = Vec3f(0.0,-1.0, 1.0);
    m_grad[10] = Vec3f(0.0, 1.0,-1.0);
    m_grad[11] = Vec3f(0.0,-1.0,-1.0);
    
    m_grad[12] = Vec3f(1.0, 1.0, 0.0);
    m_grad[13] = Vec3f(-1.0, 1.0, 0.0);
    m_grad[14] = Vec3f(0.0,-1.0, 1.0);
    m_grad[15] = Vec3f(0.0,-1.0,-1.0);
    
    for(int i = 0; i < 16; i++)
	m_phi[i] = i;
    
    // Shuffle phi
    for(int i = 14; i >= 0; i--){
	int target = rand() % (i + 1);
	int temp = m_phi[i + 1];

	m_phi[i + 1] = m_phi[target];
	m_phi[target] = temp;
    }
}

float Noise::turbulence(const Vec3f &p, int depth) const {
    float sum = 0.0f;
    float weight = 1.0f;
    Vec3f ptemp(p);
    
    sum = fabs(noise(ptemp));
    
    for(int i = 1; i < depth; i++){
	weight = weight * 2;
	
	ptemp[0] = p.x() * weight;
	ptemp[1] = p.y() * weight;
	ptemp[2] = p.z() * weight;
	
	sum += fabs(noise(ptemp)) / weight;
    }
    
    return sum;
}

float Noise::dturbulence(const Vec3f &p, int depth, float d) const {
    float sum = 0.0f;
    float weight = 1.0f;
    Vec3f ptemp(p);
    
    sum += fabs(noise(ptemp)) / d;
    
    for(int i = 1; i < depth; i++){
	weight = weight * d;
	
	ptemp[0] = p.x() * weight;
	ptemp[1] = p.y() * weight;
	ptemp[2] = p.z() * weight;
	
	sum += fabs(noise(ptemp)) / d;
    }
    
    return sum;
}

float Noise::noise(const Vec3f &p) const {
    int fi, fj, fk;
    float fu, fv, fw, sum;
    Vec3f v;
    
    fi = int(floor(p.x()));
    fj = int(floor(p.y()));
    fk = int(floor(p.z()));
    
    fu = p.x() - float(fi);
    fv = p.y() - float(fj);
    fw = p.z() - float(fk);
    
    sum = 0.0;
    
    v = Vec3f(fu, fv, fw);
    sum += knot(fi, fj, fk, v);
    
    v = Vec3f(fu - 1, fv, fw);
    sum += knot(fi + 1, fj, fk, v);
    
    v = Vec3f(fu, fv - 1, fw);
    sum += knot(fi, fj + 1, fk, v);
    
    v = Vec3f(fu, fv, fw - 1);
    sum += knot(fi, fj, fk + 1, v);
    
    v = Vec3f(fu - 1, fv - 1, fw);
    sum += knot(fi + 1, fj + 1, fk, v);
    
    v = Vec3f(fu - 1, fv, fw - 1);
    sum += knot(fi + 1, fj, fk + 1, v);
    
    v = Vec3f(fu, fv - 1, fw - 1);
    sum += knot(fi, fj + 1, fk + 1, v);
    
    v = Vec3f(fu - 1, fv - 1, fw - 1);
    sum += knot(fi + 1, fj + 1, fk + 1, v);
    
    return sum;
}
