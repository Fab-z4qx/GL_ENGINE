#pragma once
#include "mesh.h"
#include <cmath>

namespace e3d {

class Sphere : public Mesh
{
private:
	double _r; //rayon
	double _rings,
		_segments;

public:
	Sphere(const string& name,Vector4 center, double radius, double nbLogitude, double nbLatitude);
    Sphere(const string& name,Vector4 center, double r, double n);
	~Sphere(void);

};


}
